#pragma once

namespace vehicle {

// All Newtons (N)
    struct Forces {
        double traction_N = 0.0; // input
        double drag_N = 0.0;     // computed
        double rolling_N = 0.0;  // computed
    };
}