#pragma once

namespace sim {

    struct SimulationTime {
        double real_dt;     // Wall-clock delta (seconds)
        double sim_dt;      // Fixed simulation step (seconds)
        double sim_time;    // Total simulated time (seconds)
        double time_scale;  // 1.0 = real-time
    };
}