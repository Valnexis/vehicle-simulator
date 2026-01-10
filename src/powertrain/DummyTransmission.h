#pragma once
#include "Transmission.h"

class DummyTransmission : public Transmission {
public:
    int currentGear() const override {return 1;}

    units::Torque transmit(units::Torque torque) override {
        return torque * 0.9;
    }
};