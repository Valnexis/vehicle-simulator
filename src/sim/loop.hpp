#pragma once

#include <functional>
#include "time.hpp"

namespace sim {

class SimulationLoop {
public:
    using UpdateFn = std::function<void(const SimulationTime&)>;

    explicit SimulationLoop(double fixed_dt)
        : m_fixed_dt(fixed_dt) {}

    void run(UpdateFn update);

private:
    double m_fixed_dt;
};
}