# Architecture Principles

## Simulation
- Fixed timestep only
- Deterministic execution
- No rendering dependency

## Units
- SI units internally
- UI converts units, physics never does

## Modularity
- Engine, ECU, transmission are independent
- Vehicle is a composition layer only