#include <iostream>
#include <chrono>
#include <thread>

#include "controls/DriverInputs.h"
#include "controls/DriverController.h"
#include "controls/SDLKeyboard.h"

#include "drivetrain/Gearbox.h"
#include "powertrain/ManualTransmission.h"

#include "vehicle/Vehicle.h"
#include "vehicle/VehicleState.h"

#include "engine/engine.hpp"
#include "engine/torque_curve.hpp"

int main() {
    constexpr double dt = 1.0 / 60.0;

    // -----------------------------
    // Input system
    // -----------------------------
    DriverInputs inputs;
    DriverController controller;

    SDLKeyboard keyboard;
    SDLKeyboardState keys;

    if (!keyboard.ok()) {
        std::cerr << "SDL keyboard init failed.\n";
        return 1;
    }

    // -----------------------------
    // Vehicle state
    // -----------------------------
    VehicleState vehicleState;

    // -----------------------------
    // Gearbox & transmission
    // -----------------------------
    Gearbox gearbox;
    ManualTransmission transmission(gearbox);

    // -----------------------------
    // Engine setup
    // -----------------------------
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

    // -----------------------------
    // Vehicle (powertrain owner)
    // -----------------------------
    Vehicle vehicle(engine, transmission, vehicleState);

    // -----------------------------
    // Runtime state
    // -----------------------------
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

    // =============================
    // Main loop
    // =============================
    while (running) {
        keyboard.poll(keys);

        if (keys.quit)
            running = false;

        // -------------------------
        // Driver input update
        // -------------------------
        controller.update(
            inputs,
            dt,
            keys.throttle,
            keys.brake,
            keys.clutch
        );

        // -------------------------
        // Gear shifting
        // -------------------------
        if (keys.gearDown && keys.clutch)
            transmission.shiftDown();

        if (keys.gearUp && keys.clutch)
            transmission.shiftUp();

        transmission.setClutch(inputs.clutch);

        // -------------------------
        // Vehicle step (ALL physics)
        // -------------------------
        vehicle.step(dt, inputs);

        time += dt;

        // -------------------------
        // Telemetry (≈10 Hz)
        // -------------------------
        if (++frame % 6 == 0) {
            std::system("clear");

            std::cout << "Time:     " << time << " s\n";
            std::cout << "Speed:    " << vehicleState.speedKmh() << " km/h\n";

            std::cout << "\n--- Engine ---\n";
            std::cout << "RPM:      " << engine.getRPM() << "\n";
            std::cout << "Torque:   " << engine.getTorque() << " Nm\n";
            std::cout << "Power:    " << engine.getPowerKW() << " kW\n";

            std::cout << "\n--- Drivetrain ---\n";
            std::cout << "Gear:     " << transmission.currentGear() << "\n";
            std::cout << "Wheel Tq: " << vehicle.wheelTorque() << " Nm\n";

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
        }

        std::this_thread::sleep_for(
            std::chrono::duration<double>(dt)
        );
    }

    std::cout << "\nSimulation exited cleanly.\n";
    return 0;
}