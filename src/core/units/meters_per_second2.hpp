#pragma once
#include <ostream>

namespace units {

struct MetersPerSecond2 {
    double value;
    constexpr explicit MetersPerSecond2(double v = 0.0) : value(v) {}
};

inline std::ostream& operator<<(std::ostream& os, const MetersPerSecond2& a) {
    return os << a.value;
}
}