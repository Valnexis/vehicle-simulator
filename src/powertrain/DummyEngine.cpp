#include "DummyEngine.h"

DummyEngine::~DummyEngine() = default;

units::RPM DummyEngine::rpm() const {
    return 1000.0;
}

units::Torque DummyEngine::outputTorque() const {
    return 120.0;
}

void DummyEngine::setThrottle(double) {
}

void DummyEngine::step(double) {
}
