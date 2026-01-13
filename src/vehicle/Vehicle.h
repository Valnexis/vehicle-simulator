#pragma once

#include "../controls/DriverInputs.h"
#include "../engine/engine.hpp"
#include "../powertrain/ManualTransmission.h"
#include "VehicleState.h"

class Vehicle {
public:
    Vehicle(
        Engine& engine,
        ManualTransmission& transmission,
        VehicleState& state
    );

    void step(double dt, const DriverInputs& inputs);

    double wheelTorque() const;

private:
    Engine& m_engine;
    ManualTransmission& m_transmission;
    VehicleState& m_state;

    double m_wheelTorque = 0.0;
};