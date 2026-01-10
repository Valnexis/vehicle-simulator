#pragma once
#include "angular_velocity.hpp"
#include <numbers>

namespace units {

struct Rpm {
    double value;

    constexpr explicit Rpm(double v = 0.0) : value(v) {}
};

// Conversion helpers
constexpr RadiansPerSecond to_rad_per_sec(Rpm rpm) {
    return RadiansPerSecond(
        rpm.value * 2.0 * std::numbers::pi / 60.0
    );
}

    constexpr Rpm to_rpm(RadiansPerSecond w) {
    return Rpm(
        w.value * 60.0 / (2.0 * std::numbers::pi)
    );
}
}