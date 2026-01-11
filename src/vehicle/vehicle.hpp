#pragma once
#include "vehicle_spec.hpp"
#include "vehicle_state.hpp"
#include "vehicle_dynamics.hpp"

namespace vehicle {

class Vehicle {
public:
    explicit Vehicle(VehicleSpec spec) : spec_(spec) {}

    VehicleState& state() {return state_;}
    const VehicleState& state() const {return state_;}
    const VehicleSpec& spec() const {return spec_;}

    StepResult update(double traction_force_N, units::Seconds dt) {
        return step_longitudinal(spec_, state_, traction_force_N, dt);
    }

private:
    VehicleSpec spec_;
    VehicleState state_{};
};
}