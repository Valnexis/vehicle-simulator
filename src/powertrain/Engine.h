#pragma once
#include "../core/Units.h"

class Engine {
public:
    virtual ~Engine() = default;

    virtual units::RPM rpm() const = 0;
    virtual units::Torque outputTorque() const = 0;

    virtual void setThrottle(double throttle) = 0;
    virtual void step(double dt) = 0;
};