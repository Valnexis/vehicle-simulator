#pragma once
#include <vector>

struct Gearbox {
    int currentGear = 1;
    std::vector<double> gearRatios {
    -3.5,
    0.0,
    3.82,
    2.20,
    1.52,
    1.22,
    1.02,
    0.84
    };
    double finalDrive = 3.91;

    double currentRatio() const {
        return gearRatios[currentGear] * finalDrive;
    }
};