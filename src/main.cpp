#include <iostream>
#include "sim/loop.hpp"
#include "vehicle/vehicle.hpp"

int main() {
    // Fixed timestep: 10 ms
    sim::SimulationLoop loop(0.01);

    // --- Vehicle specification (physical constants)
    vehicle::VehicleSpec spec{};
    spec.mass_kg = 1500.0;
    spec.frontal_area_m2 = 2.2;
    spec.drag_coefficient = 0.30;
    spec.rolling_resistance_coeff = 0.012;

    // --- Vehicle instance (STATE lives here)
    vehicle::Vehicle car{spec};

    // --- Run simulation
    loop.run([&car](const sim::SimulationTime& time) {
        constexpr double traction_force_N = 6000.0;

        car.update(traction_force_N, time.sim_dt);

        const double speed_mps = car.state().velocity.value;
        const double speed_kmh = speed_mps * 3.6;

        std::cout
            << "t=" << time.sim_time.value << " s | "
            << "v=" << speed_kmh << " km/h | "
            << "x=" << car.state().position.value << " m\n";
    });

    return 0;
}