#include "Simulation.h"

Simulation::Simulation(double timestepSeconds)
    : m_time(0.0), m_dt(timestepSeconds) {}

void Simulation::step() {
    m_time += m_dt;
}

double Simulation::time() const {
    return m_time;
}