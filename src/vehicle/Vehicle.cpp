#include "Vehicle.h"

Vehicle::Vehicle(Engine* engine, Transmission* transmission)
    : m_engine(engine), m_transmission(transmission) {}

void Vehicle::step(double dt) {
    m_engine->step(dt);
    m_transmission->transmit(m_engine->outputTorque());
}