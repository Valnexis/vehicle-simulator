#pragma once

namespace units {

struct Seconds {
    double value;

    constexpr explicit Seconds(double v = 0.0) : value(v) {}

    constexpr Seconds operator+(Seconds other) const {
        return Seconds(value + other.value);
    }

    constexpr Seconds operator-(Seconds other) const {
        return Seconds(value - other.value);
    }

    constexpr Seconds operator*(double scalar) const {
        return Seconds(value * scalar);
    }

    constexpr bool operator>=(Seconds other) const {
        return value >= other.value;
    }

    constexpr bool operator<(Seconds other) const {
        return value < other.value;
    }
};
}