#pragma once

namespace units {

struct Radians {
    double value;

    constexpr explicit Radians(double v = 0.0) : value(v) {}

    constexpr Radians operator+(Radians o) const {
        return Radians(value + o.value);
    }

    constexpr Radians operator*(double s) const {
        return Radians(value * s);
    }
};
}