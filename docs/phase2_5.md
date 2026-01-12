# Phase 2.5 — Driver Controls, Gearing & Vehicle State

## Purpose

Phase 2.5 acts as a **bridge phase** between Vehicle Dynamics (Phase 2) and the Powertrain / Engine system (Phase 3).

Its goal is to stabilize:
- driver input handling
- drivetrain control logic
- vehicle state representation
- simulation infrastructure

**No engine physics are implemented in this phase.**

---

## Scope

### What Phase 2.5 Includes
- Analog driver inputs (throttle, brake, clutch)
- Keyboard-based control system
- Proper key down / key up handling
- Transmission and gearing model
- Vehicle longitudinal state (speed)
- Deterministic simulation loop
- Engineering-grade terminal telemetry

### What Phase 2.5 Explicitly Excludes
- Engine torque production
- RPM dynamics
- Fuel, ignition, or thermal models
- Aerodynamics or downforce
- Tire models or slip calculations

These are intentionally deferred to Phase 3+.

---

## Input System

### Input Backend
- **SDL2** is used as the input backend
- A visible SDL window is created solely to receive keyboard focus
- Terminal input is **not** used for control (debug only)

### Control Mapping

| Key | Action |
|----|-------|
| W | Increase throttle (analog) |
| S | Increase brake (analog) |
| SHIFT | Engage clutch |
| Z | Gear down |
| X | Gear up |
| Q | Quit simulation |

### Design Notes
- Inputs are treated as **states**, not events
- Holding a key produces continuous input
- Modifier keys (SHIFT) work correctly
- Input layer is isolated from simulation logic

---

## Driver Input Model

### DriverInputs
Represents normalized pedal positions:

- `throttle` ∈ [0.0, 1.0]
- `brake` ∈ [0.0, 1.0]
- `clutch` ∈ [0.0, 1.0]

### DriverController
- Applies smoothing and decay
- Converts binary key states into analog pedal values
- Owns no vehicle or drivetrain logic

---

## Transmission & Gearing

### Gearbox Model
- Discrete gears with configurable ratios
- Final drive ratio
- Neutral gear (zero ratio)
- Reverse gear supported

### Shifting Rules
- Gear changes require clutch engagement
- Shifting logic is deterministic
- No engine dependency exists at this stage

---

## Vehicle State

### VehicleState
Tracks longitudinal motion only:

- Vehicle speed stored in **m/s**
- Conversion utility for km/h

No position, orientation, or wheel state is included yet.

---

## Dummy Longitudinal Model

To make controls and gearing observable, a **temporary placeholder model** is used:

- Throttle produces acceleration scaled by gear ratio
- Brake produces fixed deceleration
- Simple drag term simulates rolling + aero losses
- Clutch disengages drivetrain
- Neutral gear blocks acceleration

This model is:
- intentionally simple
- non-physical
- clearly marked as temporary

It exists solely to validate control and drivetrain flow.

---

## Simulation Loop

- Fixed timestep (60 Hz)
- Deterministic update order:
    1. Input polling
    2. Driver input update
    3. Gear logic
    4. Vehicle state update
    5. Telemetry output
- Clean shutdown on user request

---

## Telemetry

Displayed in terminal at reduced frequency (~10 Hz):

- Simulation time
- Vehicle speed (km/h)
- Throttle / brake / clutch (%)
- Current gear
- Current effective gear ratio

Telemetry is intended for **engineering inspection**, not UI.

---

## Architecture Summary

Phase 2.5 establishes clean separation between:

- **Input** (`controls/`)
- **Drivetrain** (`drivetrain/`)
- **Vehicle state** (`vehicle/`)
- **Simulation orchestration** (`main / sim`)

No module depends on engine internals.

---

## Phase Completion Criteria

Phase 2.5 is considered complete when:

- Driver inputs are stable and analog
- Gears and clutch behave correctly
- Vehicle speed responds meaningfully
- No engine assumptions exist
- Phase 3 can be implemented without refactoring Phase 2.5 code

All criteria are met.

---

## Next Phase

Phase 3 will introduce:
- EngineState
- RPM dynamics
- Torque generation
- Engine–clutch–gearbox coupling

Phase 2.5 remains unchanged during Phase 3.

---

**Phase 2.5 status: COMPLETE**