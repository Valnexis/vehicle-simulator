#pragma once
#include "engine_constants.hpp"

struct ECUState {
    bool idleControlActive = false;
    bool revLimiterActive = false;
};

class ECU {
public:
    double applyIdleControl(double rpm, double idleRPM) {
        if (rpm >= idleRPM)
            return 0.0;

        double error = idleRPM - rpm;
        return clamp(error * 0.002, 0.0, 0.2);
    }

    bool shouldCutFuel(double rpm, double redlineRPM) {
        return rpm >= redlineRPM;
    }

private:
    double clamp(double v, double min, double max) {
        if (v < min) return min;
        if (v > max) return max;
        return v;
    }
};