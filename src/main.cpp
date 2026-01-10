#include <iostream>
#include "sim/Simulation.h"
#include "powertrain/DummyEngine.h"
#include "powertrain/DummyTransmission.h"
#include "vehicle/Vehicle.h"

int main() {
    Simulation sim(0.001); // 1ms

    DummyEngine engine;
    DummyTransmission transmission;
    Vehicle vehicle(&engine, &transmission);

    for (int i = 0; i < 5000; ++i) {
        vehicle.step(0.001);
        sim.step();
    }

    std::cout << "Simulation time: " << sim.time() << " seconds\n";
}