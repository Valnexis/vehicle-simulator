#include <iostream>
#include "sim/loop.hpp"
#include "core/rotating_body.hpp"
#include "core/units/rotational/rpm.hpp"

int main() {
    sim::SimulationLoop loop(0.01);

    RotatingBody::Params p;
    p.inertia = units::KilogramMeterSquared{0.15};
    p.viscous = units::NewtonMeterPerRadPerSec{0.08}; // drag
    p.coulomb = units::NewtonMeter{2.0};              // friction
    p.stop_epsilon_rad_per_sec = 0.3;

    RotatingBody shaft{p};

    loop.run([&](const sim::SimulationTime& time) {
        // "engine torque"
        shaft.add_torque(units::NewtonMeter{120.0});

        // pretend drivetrain load (negative torque)
        shaft.set_external_load(units::NewtonMeter{-30.0});

        shaft.integrate(time.sim_dt);

        const auto rpm = units::to_rpm(shaft.velocity());
        std::cout << rpm.value << "\n";
    });

    return 0;
}