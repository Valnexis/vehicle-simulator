#pragma once
#include "Engine.h"

class DummyEngine : public Engine {
public:
    units::RPM rpm() const override {return 1000.0;}
    units::Torque outputTorque() const override {return 120.0;}

    void setThrottle(double throttle) override;
    void step(double dt) override;
};