#pragma once

#include "units/rotational/angular_velocity.hpp"
#include "units/rotational/angular_acceleration.hpp"
#include "units/rotational/dynamics.hpp"
#include "units/inertia.hpp"

class RotatingBody {
public:
    explicit RotatingBody(units::KilogramMeterSquared inertia)
        : m_inertia(inertia) {}

    void apply_torque(units::NewtonMeter torque) {
        m_acceleration =
            units::angular_acceleration(torque, m_inertia);
    }

    void integrate(units::Seconds dt) {
        // Semi-implicit Euler (stable for mechanical systems)
        m_velocity = units::RadiansPerSecond(
            m_velocity.value + m_acceleration.value * dt.value
        );
    }

    units::RadiansPerSecond velocity() const {
        return m_velocity;
    }

private:
    units::KilogramMeterSquared m_inertia;
    units::RadiansPerSecond m_velocity{0.0};
    units::RadiansPerSecondSquared m_acceleration{0.0};
};