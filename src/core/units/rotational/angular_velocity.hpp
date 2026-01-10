#pragma once
#include "../seconds.hpp"
#include "radians.hpp"

namespace units {

struct RadiansPerSecond {
    double value;

    constexpr explicit RadiansPerSecond(double v = 0.0) : value(v) {}

    constexpr Radians operator*(Seconds dt) const {
        return Radians(value * dt.value);
    }
};
}