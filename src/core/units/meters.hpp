#pragma once
#include <ostream>

namespace units {

struct Meters {
    double value;
    constexpr explicit Meters(double v = 0.0) : value(v) {}
};

    inline std::ostream& operator<<(std::ostream& os, const Meters& m) {
        return os << m.value;
    }
}