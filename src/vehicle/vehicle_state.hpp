#pragma once
#include "../core/units/meters.hpp"
#include "../core/units/meters_per_second.hpp"
#include "../core/units/meters_per_second2.hpp"

namespace vehicle {

struct VehicleState {
    units::Meters position{0.0};
    units::MetersPerSecond velocity{0.0};
    units::MetersPerSecond2 acceleration{0.0};
};
}