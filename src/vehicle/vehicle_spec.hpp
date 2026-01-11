#pragma once
namespace vehicle {

// All SI units
struct VehicleSpec {
    double mass_kg = 1500.0;

    // Aero
    double frontal_area_m2 = 2.2;
    double drag_coefficient = 0.30;
    double air_density_kg_m3 = 1.225; // sea level default

    // Rolling resistance
    double rolling_resistance_coeff = 0.012;

    // For later phases; not used yet
    double wheel_radius_m = 0.32;
};
}