# Vehicle Engine & ECU Simulator

![License](https://img.shields.io/badge/license-MIT-green)
![C++](https://img.shields.io/badge/C%2B%2B-20-blue)
![Platform](https://img.shields.io/badge/platform-macOS%20%7C%20Linux%20%7C%20Windows-lightgrey)

A **deterministic, engineering-focused vehicle powertrain simulator** written in modern **C++20**.

This project is **not a game** and not a graphics showcase. It is a system-level simulator designed to model vehicle powertrain behavior with clean architecture, correctness, and extensibility as first-class goals.

---

## 🎯 Project Goals

- Deterministic, fixed-timestep simulation
- Clean separation between mechanics and control logic
- Modular engine, ECU, transmission, and drivetrain design
- Data-driven configuration (planned)
- Cross-platform desktop support (macOS, Linux, Windows)
- Educational and research-oriented codebase

---

## 🚫 Explicit Non-Goals

This project intentionally does **not** aim to be:

- A game or racing simulator
- A real-time graphics or rendering engine
- A multiplayer or networking system
- A physics playground optimized for visuals

The focus is on **correct system modeling**, similar in spirit to automotive, control, and hardware-in-the-loop simulators.

---

## 🧱 Architecture Overview

The simulator is structured around **clear responsibility boundaries** and **composition over inheritance**.

### High-level modules

```text
src/
├─ core/        # Unit definitions and math conventions
├─ sim/         # Simulation loop and time management
├─ powertrain/  # Engine, ECU, transmission, drivetrain abstractions
├─ vehicle/     # Vehicle composition and integration layer
└─ main.cpp     # Application entry point
```

### Core design principles

- Fixed-timestep simulation (deterministic)
- SI units internally (Nm, kg, m/s, rad/s)
- No OS- or platform-specific logic
- No rendering or frame-based assumptions
- Engine, ECU, and drivetrain are independent systems
- Vehicle acts purely as a composition layer

---

## ⏱ Simulation Model

- Fixed timestep (currently **1 ms**)
- Simulation time is fully decoupled from wall-clock time
- Same inputs always produce the same outputs

This design mirrors real-world automotive simulation and control environments.

---

## 🧪 Current Status

### ✅ Phase 0 — Completed

Phase 0 establishes the **foundation and architecture**, without implementing real physics yet.

Implemented in Phase 0:
- Deterministic simulation loop
- Engine and transmission interfaces
- Vehicle composition layer
- Dummy powertrain implementations
- Clean CMake-based build system
- Verified build on macOS (Apple Silicon)

Example output:

```text
Simulation time: 5 seconds
```

---

## 🛠 Build Instructions

### Requirements

- CMake ≥ 3.20
- C++20-compatible compiler
    - macOS: Apple clang
    - Linux: GCC or clang
    - Windows: MSVC (planned)

### Build (macOS / Linux)

```bash
git clone https://github.com/<your-username>/vehicle-simulator.git
cd vehicle-simulator
mkdir build && cd build
cmake ..
cmake --build .
./bin/vehicle_simulator
```

---

## 📌 Development Roadmap

- **Phase 0** — Core architecture & deterministic simulation loop ✅
- **Phase 1** — Engine core physics (torque generation, inertia, friction)
- **Phase 2** — ECU logic (idle control, throttle mapping, rev limiter)
- **Phase 3** — Transmission, clutch, and drivetrain modeling
- **Phase 4** — Vehicle longitudinal dynamics and tire interaction
- **Phase 5+** — Advanced powertrains (turbocharging, diesel, AWD), telemetry, analysis tools

Each phase is developed incrementally with strict architectural boundaries.

---

## 📄 License

This project is licensed under the **MIT License**. See the `LICENSE` file for details.

---

## ✍️ Author

Ilgın Yılmaz  
Computer Engineering Student  
Founder — Infera Software

This project is part of a long-term effort to explore realistic vehicle simulation, system architecture, and automotive software design.
