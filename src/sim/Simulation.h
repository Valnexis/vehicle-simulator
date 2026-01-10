#pragma once

class Simulation {
public:
    explicit Simulation(double timestepSeconds);

    void step();
    double time() const;

private:
    double m_time;
    double m_dt;
};