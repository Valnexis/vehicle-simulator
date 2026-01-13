#pragma once

#include "Transmission.h"
#include "../drivetrain/Gearbox.h"

class ManualTransmission : public Transmission {
public:
    explicit ManualTransmission(Gearbox gearbox);

    // Driver actions
    void setClutch(double engagement); // 0.0 - 1.0
    void shiftUp();
    void shiftDown();
    void setNeutral();

    // Transmission interface
    int currentGear() const override;
    units::Torque transmit(units::Torque engineTorque) override;

    double gearboxRatio() const;

private:
    Gearbox gearbox;
    double clutch = 1.0;
};