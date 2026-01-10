#pragma once
#include "../core/Units.h"

class Transmission {
public:
    virtual ~Transmission() = default;

    virtual int currentGear() const = 0;
    virtual units::Torque transmit(units::Torque engineTorque) = 0;
};