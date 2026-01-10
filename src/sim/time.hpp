#pragma once
#include "core/units/seconds.hpp"

namespace sim {

struct SimulationTime {
    units::Seconds real_dt{0.0};
    units::Seconds sim_dt{0.0};
    units::Seconds sim_time{0.0};
    double time_scale{1.0};
};
}