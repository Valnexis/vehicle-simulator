#include "DummyTransmission.h"

DummyTransmission::~DummyTransmission() = default;

int DummyTransmission::currentGear() const {
    return 1;
}

units::Torque DummyTransmission::transmit(units::Torque torque) {
    return torque * 0.9;
}
