#pragma once

namespace units {

struct KilogramMeterSquared {
    double value;
    constexpr explicit KilogramMeterSquared(double v = 0.0) : value(v) {}
};
}