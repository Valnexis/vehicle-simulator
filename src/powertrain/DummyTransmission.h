#pragma once
#include "Transmission.h"

class DummyTransmission : public Transmission {
public:
    DummyTransmission() = default;
    ~DummyTransmission() override;

    int currentGear() const override;
    units::Torque transmit(units::Torque torque) override;
};