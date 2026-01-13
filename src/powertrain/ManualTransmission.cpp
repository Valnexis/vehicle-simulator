#include "ManualTransmission.h"
#include <algorithm>

ManualTransmission::ManualTransmission(Gearbox gearbox)
    : gearbox(std::move(gearbox)) {}

void ManualTransmission::setClutch(double engagement) {
    clutch = std::clamp(engagement, 0.0, 1.0);
}

void ManualTransmission::shiftUp() {
    if (gearbox.currentGear + 1 < static_cast<int>(gearbox.gearRatios.size())) {
        gearbox.currentGear++;
    }
}

void ManualTransmission::shiftDown() {
    if (gearbox.currentGear - 1 >= 0) {
        gearbox.currentGear--;
    }
}

void ManualTransmission::setNeutral() {
    gearbox.currentGear = 1; // index 1 -> 0.0 ratio
}

int ManualTransmission::currentGear() const {
    return gearbox.currentGear;
}

double ManualTransmission::gearboxRatio() const {
    return std::abs(gearbox.currentRatio());
}

units::Torque ManualTransmission::transmit(units::Torque engineTorque) {
    const double ratio = gearbox.currentRatio();

    // Neutral or clutch disengaged
    if (ratio == 0.0 || clutch <= 0.0) {
        return units::Torque{0.0};
    }

    return engineTorque * ratio * clutch;
}
