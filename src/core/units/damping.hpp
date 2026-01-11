#pragma once

namespace units {

struct NewtonMeterPerRadPerSec {
    double value;
    constexpr explicit NewtonMeterPerRadPerSec(double v = 0.0) : value(v) {}
};
}