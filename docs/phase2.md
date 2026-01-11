# Phase 2 – Vehicle Dynamics Core [Completed at 11.01.2025]

## Goal
Establish a physically-correct, deterministic **longitudinal vehicle dynamics model**.
At the end of Phase 2, the simulator can move a vehicle realistically **given a traction force**.

Phase 2 answers **one question only**:
> If a force is applied to a vehicle, how does it move over time?

No engine, no RPM, no drivetrain.

---

## Scope (What Exists in Phase 2)

### ✅ Vehicle Physical Specification
Static, configuration-only data.

- Mass (kg)
- Frontal area (m²)
- Drag coefficient (Cd)
- Rolling resistance coefficient
- Wheel radius (stored for later phases)

```cpp
struct VehicleSpec {
    double mass_kg;
    double frontal_area_m2;
    double drag_coefficient;
    double rolling_resistance_coeff;
    double wheel_radius_m;
};
```

---

### ✅ Vehicle State (Dynamic)
Runtime data that evolves every simulation tick.

```cpp
struct VehicleState {
    units::Meters position;
    units::MetersPerSecond velocity;
    units::MetersPerSecond2 acceleration;
};
```

---

### ✅ Longitudinal Forces
Only straight-line motion is modeled.

- Traction force (input)
- Aerodynamic drag
- Rolling resistance

```cpp
struct Forces {
    double traction_N;
    double drag_N;
    double rolling_N;
};
```

---

### ✅ Physics Models

#### Aerodynamic Drag
```
F_drag = 0.5 * rho * Cd * A * v²
```

#### Rolling Resistance
```
F_roll = Crr * m * g
```

---

### ✅ Integration Model

Semi-implicit Euler (deterministic, stable for fixed timestep):

```
a = F_net / m
v = v + a * dt
x = x + v * dt
```

---

## Simulation Loop Integration

- Fixed timestep
- Accumulator-based
- Vehicle updated **only** inside the loop callback

```cpp
loop.run([&](const SimulationTime& time) {
    car.update(traction_force, time.sim_dt);
});
```

---

## Observables (Phase 2 Outputs)

- Simulation time (s)
- Vehicle speed (m/s, km/h)
- Distance traveled (m)
- Acceleration (m/s²)

❌ RPM does not exist in Phase 2.

---

## Validation Results

With:
- Mass = 1500 kg
- Traction force = 6000 N
- Cd = 0.30

Result:
```
≈ 69.4 km/h in 5 seconds
```

Matches expected physics:
```
a ≈ 4.0 m/s²
```

---

## Design Rules (Strict)

- ❌ No engine logic
- ❌ No RPM
- ❌ No gears
- ❌ No torque curves
- ✅ Units everywhere
- ✅ Deterministic behavior
- ✅ Phase isolation enforced

---

## Completion Criteria (All Met)

- [x] Vehicle accelerates realistically
- [x] Drag affects acceleration
- [x] Mass influences dynamics
- [x] Fixed timestep simulation
- [x] Clean separation from future powertrain logic

---

## Phase 2 Status

🟢 **COMPLETE**

Phase 2 code is now considered **frozen**.
All future phases must *feed forces into this system*, never modify it.

---

## Next Phase Preview

**Phase 3 – Engine Core**
- Torque curve
- Throttle
- RPM
- Inertia
- Torque → traction force generation
