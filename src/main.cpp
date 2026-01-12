#include <iostream>
#include <chrono>
#include <thread>

#include "controls/DriverInputs.h"
#include "controls/DriverController.h"
#include "controls/SDLKeyboard.h"
#include "drivetrain/Gearbox.h"
#include "vehicle/VehicleState.h"
#include "engine/engine.hpp"
#include "engine/torque_curve.hpp"

int main() {
    constexpr double dt = 1.0 / 60.0;

    DriverInputs inputs;
    DriverController controller;
    Gearbox gearbox;
    VehicleState vehicle;

    SDLKeyboard keyboard;
    SDLKeyboardState keys;

    // --- Engine setup ---
    TorqueCurve torqueCurve({
        { 800,  120 },
        { 1500, 220 },
        { 3000, 300 },
        { 4500, 310 },
        { 6000, 280 },
        { 7000, 200 }
    });

    EngineSpecs engineSpecs {
        .idleRPM = 800,
        .redlineRPM = 7000,
        .inertia = 0.25,
        .frictionCoeff = 0.02
    };

    Engine engine(engineSpecs, torqueCurve);

    if (!keyboard.ok()) {
        std::cerr << "SDL keyboard init failed.\n";
        return 1;
    }

    bool running = true;
    double time = 0.0;
    int frame = 0;

    std::cout <<
        "Controls:\n"
        " W     = Throttle\n"
        " S     = Brake\n"
        " SHIFT = Clutch\n"
        " Z     = Gear Down\n"
        " X     = Gear Up\n"
        " Q     = Quit\n";

    while (running) {
        keyboard.poll(keys);

        if (keys.quit)
            running = false;

        // --- Gear logic ---
        if (keys.gearDown && keys.clutch && gearbox.currentGear > 0)
            gearbox.currentGear--;

        if (keys.gearUp &&
            keys.clutch &&
            gearbox.currentGear < (int)gearbox.gearRatios.size() - 1)
            gearbox.currentGear++;

        // --- Pedals ---
        controller.update(
            inputs,
            dt,
            keys.throttle,
            keys.brake,
            keys.clutch
        );

        double loadTorque = 0.0;

        bool drivetrainEngaged =
            !keys.clutch &&
            gearbox.currentRatio() != 0.0;

        if (drivetrainEngaged) {
            loadTorque =
                vehicle.speed * 20.0 *
                std::abs(gearbox.currentRatio());
        }

        engine.update(
            dt,
            inputs.throttle,
            loadTorque,
            vehicle.speed);

        double wheelForce = 0.0;

        if (drivetrainEngaged && engine.isRunning()) {
            double driveTorque =
                engine.getTorque() *
                gearbox.currentRatio();

            wheelForce = driveTorque / 0.32; // wheel radius (m)
        }

        double accel =
            (wheelForce / 1400.0)   // vehicle mass (kg)
            - inputs.brake * 8.0
            - 0.4 * vehicle.speed;

        vehicle.speed += accel * dt;

        if (vehicle.speed < 0.0)
            vehicle.speed = 0.0;

        if (vehicle.speed < 0.0)
            vehicle.speed = 0.0;

        time += dt;

        // --- Telemetry (10 Hz) ---
        if (++frame % 6 == 0) {
            std::system("clear");

            std::cout << "Time:     " << time << " s\n";
            std::cout << "Speed:    " << vehicle.speedKmh() << " km/h\n";

            std::cout << "\n--- Engine ---\n";
            std::cout << "RPM:      " << engine.getRPM() << "\n";
            std::cout << "Torque:   " << engine.getTorque() << " Nm\n";
            std::cout << "Power:    " << engine.getPowerKW() << " kW\n";

            std::cout << "\n--- Fuel ---\n";
            std::cout << "Tank:     "
                      << engine.getFuelTank().currentLiters
                      << " L\n";
            std::cout << "Instant:  "
                      << engine.getInstantConsumption()
                      << " L/100km\n";
            std::cout << "Average:  "
                      << engine.getConsumption().averageLper100km()
                      << " L/100km\n";

            std::cout << "\n--- Controls ---\n";
            std::cout << "Throttle: " << inputs.throttle * 100 << " %\n";
            std::cout << "Brake:    " << inputs.brake * 100 << " %\n";
            std::cout << "Clutch:   " << inputs.clutch * 100 << " %\n";
            std::cout << "Gear:     " << gearbox.currentGear << "\n";
        }

        std::this_thread::sleep_for(
            std::chrono::duration<double>(dt)
        );
    }

    std::cout << "\nSimulation exited cleanly.\n";
    return 0;
}