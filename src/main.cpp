#include <iostream>
#include <chrono>
#include <thread>

#include "controls/DriverInputs.h"
#include "controls/DriverController.h"
#include "controls/SDLKeyboard.h"
#include "drivetrain/Gearbox.h"
#include "vehicle/VehicleState.h"

int main() {
    constexpr double dt = 1.0 / 60.0;

    DriverInputs inputs;
    DriverController controller;
    Gearbox gearbox;
    VehicleState vehicle;

    SDLKeyboard keyboard;
    SDLKeyboardState keys;

    if (!keyboard.ok()) {
        std::cerr << "SDL keyboard init failed.\n";
        return 1;
    }

    bool running = true;
    double time = 0.0;
    int frame = 0;

    // --- Dummy tuning constants ---
    constexpr double maxAccel = 6.0;   // m/s² at full throttle, 1st gear
    constexpr double brakeDecel = 10.0; // m/s²
    constexpr double drag = 0.6;        // fake rolling + aero drag

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

        // --- Dummy longitudinal model ---
        double accel = 0.0;

        bool drivetrainEngaged =
            !keys.clutch &&
            gearbox.currentRatio() != 0.0;

        if (drivetrainEngaged) {
            accel += inputs.throttle *
                     maxAccel *
                     std::abs(gearbox.currentRatio());
        }

        accel -= inputs.brake * brakeDecel;
        accel -= drag * vehicle.speed;

        vehicle.speed += accel * dt;

        if (vehicle.speed < 0.0)
            vehicle.speed = 0.0;

        time += dt;

        // --- Telemetry (10 Hz) ---
        if (++frame % 6 == 0) {
            std::system("clear");
            std::cout << "Time:     " << time << " s\n";
            std::cout << "Speed:    " << vehicle.speedKmh() << " km/h\n";
            std::cout << "Throttle: " << inputs.throttle * 100 << " %\n";
            std::cout << "Brake:    " << inputs.brake * 100 << " %\n";
            std::cout << "Clutch:   " << inputs.clutch * 100 << " %\n";
            std::cout << "Gear:     " << gearbox.currentGear << "\n";
            std::cout << "Ratio:    " << gearbox.currentRatio() << "\n";
        }

        std::this_thread::sleep_for(
            std::chrono::duration<double>(dt)
        );
    }

    std::cout << "\nSimulation exited cleanly.\n";
    return 0;
}