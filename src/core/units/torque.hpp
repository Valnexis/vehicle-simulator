#pragma once

namespace units {

struct NewtonMeter {
    double value;

    constexpr explicit NewtonMeter(double v = 0.0) : value(v) {}
};
}