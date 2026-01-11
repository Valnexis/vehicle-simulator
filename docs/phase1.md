# Phase 1 – Deterministic Simulation Core

## Overview
Phase 1 establishes the **entire physical and temporal foundation** of the vehicle simulator.  
No vehicle logic, no engine combustion, no ECU strategies — only **correct, deterministic mechanics**.

This phase ensures that every future system (engine, transmission, drivetrain, vehicle dynamics)
operates on a **stable, unit-safe, and reproducible simulation core**.

---

## Goals Achieved

- Deterministic fixed-step simulation loop
- Frame-rate independent time integration
- Strongly typed physical units
- Stable rotational dynamics
- Damping, friction, and external load modeling
- Engine-ready mechanical abstraction

---

## Architecture Summary

```
src/
├─ core/
│  ├─ units/
│  │  ├─ seconds.hpp
│  │  ├─ torque.hpp
│  │  ├─ inertia.hpp
│  │  ├─ damping.hpp
│  │  └─ rotational/
│  │     ├─ radians.hpp
│  │     ├─ angular_velocity.hpp
│  │     ├─ angular_acceleration.hpp
│  │     ├─ rpm.hpp
│  │     └─ dynamics.hpp
│  ├─ rotating_body.hpp
│
├─ sim/
│  ├─ time.hpp
│  ├─ loop.hpp
│  └─ loop.cpp
│
└─ main.cpp
```

---

## Simulation Loop

- Fixed timestep (configurable, default 10 ms)
- Accumulator-based integration
- Deterministic progression independent of wall-clock jitter
- Supports time scaling (future use)

This design mirrors professional automotive and aerospace simulators.

---

## Unit System

All physical quantities are **explicitly typed**:
- `Seconds`
- `Radians`, `RadiansPerSecond`, `RadiansPerSecondSquared`
- `Rpm`
- `NewtonMeter`
- `KilogramMeterSquared`

### Benefits
- Compile-time prevention of invalid physics
- Self-documenting equations
- Zero runtime overhead
- Safer long-term scaling

---

## Rotational Dynamics Core

The `RotatingBody` abstraction models:
- Moment of inertia
- Torque accumulation
- Angular acceleration (τ = I · α)
- Semi-implicit Euler integration
- Viscous damping
- Coulomb friction
- External load torque

This component represents:
- Engine crankshafts
- Flywheels
- Electric motors
- Driveshafts
- Any rotating mechanical element

---

## Numerical Stability

- Semi-implicit Euler integration chosen for stability
- Near-zero velocity snapping prevents friction jitter
- Deterministic results across runs and machines

---

## Validation

Observed behavior:
- Smooth RPM ramp under constant torque
- Asymptotic convergence to steady-state RPM
- No oscillations or runaway values
- Fully deterministic output

This confirms correct physical modeling.

---

## Phase 1 Outcome

Phase 1 delivers a **production-grade simulation foundation**.

All subsequent phases rely on this layer without modification.

---

## Next Phase

**Phase 2 – Engine Core**
- Crankshaft model
- Torque curve
- Throttle input
- Idle control
- Engine braking
- Starter motor logic

Phase 1 is complete.
