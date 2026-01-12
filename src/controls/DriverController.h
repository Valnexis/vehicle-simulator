#pragma once
#include "DriverInputs.h"
#include <cmath>

struct DriverController {
    double throttleRate = 1.2; // per second
    double brakeRate    = 1.5;
    double releaseRate  = 2.0;

    void update(DriverInputs& in, double dt,
        bool w, bool s, bool shift) {
        if (w) in.throttle += throttleRate * dt;
        else in.throttle -= releaseRate * dt;

        if (s) in.brake += brakeRate * dt;
        else in.brake -= brakeRate * dt;

        in.clutch = shift ? 1.0 : 0.0;

        in.throttle = std::clamp(in.throttle, 0.0, 1.0);
        in.brake   = std::clamp(in.brake, 0.0, 1.0);
    }
};