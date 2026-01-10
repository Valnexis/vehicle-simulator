#include "loop.hpp"
#include <chrono>

namespace sim {

void SimulationLoop::run(UpdateFn update) {
    using clock = std::chrono::steady_clock;

    auto last = clock::now();
    double accumulator = 0.0;

    SimulationTime time{};
    time.sim_dt = m_fixed_dt;
    time.sim_time = 0.0;
    time.time_scale = 1.0;

    while (time.sim_time < 5.0) { // temporary stop condition
        auto now = clock::now();
        std::chrono::duration<double> real_delta = now - last;
        last = now;

        time.real_dt = real_delta.count();
        accumulator += time.real_dt * time.time_scale;

        while (accumulator >= time.sim_dt) {
            update(time);
            accumulator -= time.sim_dt;
            time.sim_time += time.sim_dt;
        }
    }
}
}