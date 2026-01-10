#include <iostream>
#include "sim/loop.hpp"

int main() {
    sim::SimulationLoop loop(0.01); // 10 ms fixed step

    loop.run([](const sim::SimulationTime& time) {
        std::cout << "Sim time: " << time.sim_time.value << " s\n";
    });
    return 0;
}
