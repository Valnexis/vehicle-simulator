# Phase 0 — Foundations & Architecture [Completed on 10.01.2026]

## Purpose

Phase 0 establishes the **structural and architectural foundation** of the Vehicle Engine & ECU Simulator.

No real physics or control logic is implemented in this phase by design.
The objective is to ensure that all future development rests on a **stable, deterministic, and extensible base**.

This phase focuses on **correctness, separation of concerns, and tooling**, not feature depth.

---

## Scope of Phase 0

### Included

- Deterministic, fixed-timestep simulation loop
- Core architectural layout
- Engine and transmission abstractions
- Vehicle composition layer
- Dummy powertrain implementations for validation
- Cross-platform build system using CMake
- macOS (Apple Silicon) build verification

### Explicitly Excluded

- Real engine physics
- ECU control logic
- Transmission or clutch dynamics
- Vehicle dynamics or tire models
- Rendering or visualization
- Real-time or wall-clock coupling

---

## Architectural Decisions

### Simulation Model

- Fixed timestep simulation (`Δt = 1 ms`)
- Simulation time is decoupled from real time
- Deterministic execution: same inputs always produce the same results

This mirrors real automotive and hardware-in-the-loop simulators and avoids game-style update loops.

---

### Module Responsibilities

```text
src/
├─ core/        # Unit definitions and math conventions
├─ sim/         # Simulation loop and time management
├─ powertrain/  # Engine and transmission abstractions
├─ vehicle/     # Vehicle composition layer
└─ main.cpp     # Application entry point
```

- **core/**
  Defines unit conventions and shared low-level constructs.

- **sim/**
  Owns simulation time and stepping logic. No physics lives here.

- **powertrain/**
  Defines abstract interfaces for engines and transmissions.
  Dummy implementations exist only to validate architecture.

- **vehicle/**
  Acts as a composition layer.
  It does not implement physics or control logic.

---

### Units & Conventions

- SI units are used internally:
    - Torque: Nm
    - Mass: kg
    - Speed: m/s
    - Angular velocity: rad/s
- Unit conversion is handled at system boundaries only
- Physics code never operates on display units

---

## Polymorphism & Build Correctness

- All polymorphic classes have proper translation units
- Vtable ownership is explicitly defined via `.cpp` files
- No inline virtual method definitions that cause linker ambiguity
- Headers are not attached directly to CMake targets

This ensures:
- Clean linkage on macOS arm64
- Future compatibility with shared/static libraries
- Toolchain-agnostic behavior

---

## Build System

- CMake ≥ 3.20
- Modern target-based CMake usage
- No global compiler flags
- No platform-specific conditionals in Phase 0

Verified configuration:
- macOS (Apple Silicon)
- clang++
- Ninja generator

---

## Validation

Phase 0 is considered complete when:

- The project configures successfully with CMake
- The executable builds without warnings or linker errors
- The simulation runs deterministically
- Output confirms correct simulation time progression

Example output:

```text
Simulation time: 5 seconds
```

---

## Outcome

At the end of Phase 0, the project has:

- A stable architectural backbone
- Clean separation between systems
- A deterministic simulation core
- Professional-grade build and tooling setup

This foundation enables safe progression into **Phase 1**, where real engine physics can be implemented without architectural rework.

---

## Next Phase

**Phase 1 — Engine Core Physics**

Focus areas:
- Engine rotational inertia
- RPM integration
- Torque curve modeling
- Friction and pumping losses

Phase 1 builds directly on the guarantees established in Phase 0.
