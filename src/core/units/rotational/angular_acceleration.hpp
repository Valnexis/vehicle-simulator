#pragma once
#include "../seconds.hpp"

namespace units {

struct RadiansPerSecondSquared {
    double value;
    constexpr explicit RadiansPerSecondSquared(double v = 0.0) : value(v) {}

    constexpr RadiansPerSecond operator*(Seconds dt) const {
        return RadiansPerSecond(value * dt.value);
    }
};
}