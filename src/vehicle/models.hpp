#pragma once
#include <cmath>
#include "vehicle_spec.hpp"
#include "vehicle_state.hpp"

namespace vehicle {

// F_drag = 0.5 * rho * Cd * A * v^2
inline double aerodynamic_drag_N(const VehicleSpec& s, const VehicleState& st) {
    const double v = st.velocity.value;
    return 0.5 * s.air_density_kg_m3 * s.drag_coefficient * s.frontal_area_m2 * (v * v);
}

// F_roll = Crr * m * g (opposes motion)
inline double rolling_resistence_N(const VehicleSpec& s) {
    constexpr double g = 9.80655;
    return s.rolling_resistance_coeff * s.mass_kg * g;
}
}