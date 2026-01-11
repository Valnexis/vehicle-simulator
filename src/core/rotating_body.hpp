#pragma once

#include <cmath>

#include "units/seconds.hpp"
#include "units/torque.hpp"
#include "units/inertia.hpp"
#include "units/damping.hpp"
#include "units/rotational/angular_velocity.hpp"
#include "units/rotational/angular_acceleration.hpp"
#include "units/rotational/dynamics.hpp"

class RotatingBody {
public:
    struct Params {
        units::KilogramMeterSquared inertia{0.1};

        // Viscous damping: τ = -c * ω
        units::NewtonMeterPerRadPerSec viscous{0.0};

        // Coulomb friction (static-ish): τ = -sign(ω) * friction
        units::NewtonMeter coulomb{0.0};

        // Prevent jitter around zero speed
        double stop_epsilon_rad_per_sec{0.5};
    };

    explicit RotatingBody(Params p)
        : m_params(p), m_inertia(p.inertia) {}

    // Add any torque source (combustion, motor, braking, load)
    void add_torque(units::NewtonMeter t) {
        m_net_torque = units::NewtonMeter{m_net_torque.value + t.value};
    }

    // Set an external load torque (e.g., drivetrain). This can change every tick.
    void set_external_load(units::NewtonMeter load) {
        m_external_load = load;
    }

    void integrate(units::Seconds dt) {
        // Add resistive torques based on current state
        const auto resist = compute_resistive_torque();
        const auto load   = m_external_load;

        const double total =
            m_net_torque.value + resist.value + load.value;

        const auto alpha = units::RadiansPerSecondSquared(total / m_inertia.value);

        // Semi-implicit Euler (stable)
        m_velocity = units::RadiansPerSecond(
            m_velocity.value + alpha.value * dt.value
        );

        // Snap to zero near stop to avoid sign jitter with Coulomb friction
        if (std::fabs(m_velocity.value) < m_params.stop_epsilon_rad_per_sec) {
            m_velocity = units::RadiansPerSecond{0.0};
        }

        // Reset accumulated torques for next tick
        m_net_torque = units::NewtonMeter{0.0};
        m_external_load = units::NewtonMeter{0.0};
    }
    units::RadiansPerSecond velocity() const {return m_velocity;}

private:
    units::NewtonMeter compute_resistive_torque() const {
        // Viscous drag: -c * ω
        const double visc = -m_params.viscous.value * m_velocity.value;

        // Coulomb friction: -sign(ω) * F (only if moving)
        double coul = 0.0;
        if (m_velocity.value > 0.0) coul = -m_params.coulomb.value;
        else if (m_velocity.value < 0.0) coul = m_params.coulomb.value;

        return units::NewtonMeter{visc + coul};
    }

private:
    Params m_params;
    units::KilogramMeterSquared m_inertia;

    units::RadiansPerSecond m_velocity{0.0};

    // Torque bookkeeping
    units::NewtonMeter m_net_torque{0.0};
    units::NewtonMeter m_external_load{0.0};
};