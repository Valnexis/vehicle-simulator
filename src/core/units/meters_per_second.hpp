#pragma once
#include <ostream>

namespace units {

struct MetersPerSecond {
    double value;
    constexpr explicit MetersPerSecond(double v) : value(v) {}
};

    inline std::ostream& operator<<(std::ostream& os, const MetersPerSecond& v) {
        return os << v.value;
    }
}