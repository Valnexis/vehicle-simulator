#include "Vehicle.h"
#include <cmath>

Vehicle::Vehicle(
    Engine& engine,
    ManualTransmission& transmission,
    VehicleState& state
)
    : m_engine(engine),
      m_transmission(transmission),
      m_state(state) {}

void Vehicle::step(double dt, const DriverInputs& inputs) {
    // Drivetrain engaged if clutch connected and not neutral
    const bool drivetrainEngaged =
        inputs.clutch < 0.5 &&
        m_transmission.currentGear() != 1; // index 1 = neutral

    // -------------------------
    // Load torque (engine-side)
    // -------------------------
    double loadTorque = 0.0;

    if (drivetrainEngaged) {
        // Resistance proportional to vehicle speed and gear ratio
        const double gearRatio =
            std::abs(m_transmission.gearboxRatio());

        loadTorque =
            m_state.speed * 20.0 * gearRatio;
    }

    // -------------------------
    // Engine update
    // -------------------------
    m_engine.update(
        dt,
        inputs.throttle,
        loadTorque,
        m_state.speed
    );

    // -------------------------
    // Wheel torque
    // -------------------------
    if (drivetrainEngaged && m_engine.isRunning()) {
        m_wheelTorque =
            m_transmission.transmit(m_engine.getTorque());
    } else {
        m_wheelTorque = 0.0;
    }
}

double Vehicle::wheelTorque() const {
    return m_wheelTorque;
}