#pragma once
#include "../torque.hpp"
#include "../inertia.hpp"
#include "angular_acceleration.hpp"

namespace units {

constexpr RadiansPerSecondSquared
angular_acceleration(NewtonMeter torque, KilogramMeterSquared inertia) {
    return RadiansPerSecondSquared(torque.value / inertia.value);
}
}