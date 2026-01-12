#include "engine.hpp"
#include <cmath>

Engine::Engine(const EngineSpecs& specs_, TorqueCurve curve)
    : specs(specs_), torqueCurve(std::move(curve)), fuelTank(50.0) // default 50L tank
{
    rpm = specs.idleRPM;
    omega = rpm * 2.0 * M_PI / 60.0;
}

void Engine::update(double dt, double throttleInput, double loadTorque, double vehicleSpeedMps) {
    if (!engineRunning)
        return;

    // Convert speed
    double vehicleSpeedKmh = vehicleSpeedMps * 3.6;

    // --- ECU idle assist
    double idleThrottle = ecu.applyIdleControl(rpm, specs.idleRPM);
    ecuState.idleControlActive = idleThrottle > 0.0;

    // --- Effective throttle
    double effectiveThrottle = throttleInput + idleThrottle;
    if (effectiveThrottle > 1.0)
        effectiveThrottle = 1.0;

    // --- Rev limiter
    ecuState.revLimiterActive = ecu.shouldCutFuel(rpm, specs.redlineRPM);
    if (ecuState.revLimiterActive)
        effectiveThrottle = 0.0;

    // --- Torque from curve
    double maxTorque = torqueCurve.getTorque(rpm);
    engineTorque = maxTorque * effectiveThrottle;

    // --- Friction
    double frictionTorque = specs.frictionCoeff * rpm;

    // --- Net torque
    double netTorque = engineTorque - loadTorque - frictionTorque;

    // --- Angular dynamics
    double angularAccel = netTorque / specs.inertia;
    omega += angularAccel * dt;

    if (omega < 0.0)
        omega = 0.0;

    rpm = omega * 60.0 / (2.0 * M_PI);

    // --- Stall check (RPM)
    if (rpm < STALL_RPM) {
        rpm = 0.0;
        omega = 0.0;
        engineRunning = false;
        return;
    }

    // --- Power calculation
    enginePowerKW = (engineTorque * omega) / 1000.0;

    if (enginePowerKW < 0.0)
        enginePowerKW = 0.0;

    // --- Fuel consumption
    double fuelFlowKgps = fuelFlowKgPerSec(enginePowerKW);
    double fuelFlowLps  = fuelFlowLitersPerSec(fuelFlowKgps);

    // Burn fuel
    double fuelUsed = fuelFlowLps * dt;
    fuelTank.consume(fuelUsed);

    // Track totals
    consumption.totalFuelUsedLiters += fuelUsed;
    consumption.totalDistanceKm += vehicleSpeedKmh * dt / 3600.0;

    // Instant consumption
    instantLper100km = instantConsumptionLper100km(fuelFlowLps, vehicleSpeedKmh);

    // --- Fuek empty -> engine dies
    if (fuelTank.isEmpty()) {
        rpm = 0.0;
        omega = 0.0;
        engineTorque = 0.0;
        engineRunning = false;
    }
}