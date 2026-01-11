#pragma once
#include <algorithm>
#include "../core/units/ops.hpp"
#include "vehicle_spec.hpp"
#include "vehicle_state.hpp"
#include "forces.hpp"
#include "models.hpp"

namespace vehicle {

struct StepResult {
    Forces forces;
};

inline StepResult step_longitudinal(
    const VehicleSpec& spec,
    VehicleState& state,
    double traction_force_N,
    units::Seconds dt
) {
    StepResult out{};
    out.forces.traction_N = traction_force_N;

    // resistances
    out.forces.drag_N = aerodynamic_drag_N(spec, state);
    out.forces.rolling_N = rolling_resistence_N(spec);

    // rolling/drag should oppose motion direction (simple 1D sign handling)
    const double v = state.velocity.value;
    const double sign = (v > 0.0) ? 1.0 : (v < 0.0 ? -1.0 : 0.0);

    const double resist_N = out.forces.drag_N * sign + out.forces.rolling_N * sign;

    // Net force
    const double net_N = traction_force_N - resist_N;

    // a = F/m
    state.acceleration = units::MetersPerSecond2{net_N / spec.mass_kg};

    // Integrate (semi-implicit Euler; stable enough for this)
    state.velocity = state.velocity + (state.acceleration * dt);
    state.position = state.position + (state.velocity * dt);

    // prevent tiny numerical reverse creep near zero if traction is 0
    if (std::abs(state.velocity.value) < 1e-6) {
        state.velocity = units::MetersPerSecond{0.0};
    }

    return out;
}
}