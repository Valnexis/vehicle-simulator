#include "loop.hpp"
#include <chrono>

namespace sim {

void SimulationLoop::run(UpdateFn update) {
    using clock = std::chrono::steady_clock;

    auto last = clock::now();
    units::Seconds accumulator{0.0};

    SimulationTime time{};
    time.sim_dt = units::Seconds{m_fixed_dt};
    time.sim_time = units::Seconds{0.0};
    time.time_scale = 1.0;

    while (time.sim_time < units::Seconds{5.0}) {
        auto now = clock::now();
        std::chrono::duration<double> real_delta = now - last;
        last = now;

        time.real_dt = units::Seconds{real_delta.count()};
        accumulator = accumulator + (time.real_dt * time.time_scale);

        while (accumulator >= time.sim_dt) {
            update(time);
            accumulator = accumulator - time.sim_dt;
            time.sim_time = time.sim_time + time.sim_dt;
        }
    }
}

} // namespace sim