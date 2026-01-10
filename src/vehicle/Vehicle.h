#pragma once
#include "../powertrain/Engine.h"
#include "../powertrain/Transmission.h"

class Vehicle {
public:
    Vehicle(Engine* engine, Transmission* transmission);

    void step(double dt);

private:
    Engine* m_engine;
    Transmission* m_transmission;
};