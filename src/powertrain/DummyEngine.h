#pragma once
#include "Engine.h"

class DummyEngine : public Engine {
public:
    DummyEngine() = default;
    ~DummyEngine() override;

    units::RPM rpm() const override;
    units::Torque outputTorque() const override;

    void setThrottle(double throttle) override;
    void step(double dt) override;
};