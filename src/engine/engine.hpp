#pragma once

#include "fuel_math.hpp"
#include "fuel_system.hpp"
#include "engine_constants.hpp"
#include "torque_curve.hpp"
#include "ecu.hpp"

struct EngineSpecs {
    double idleRPM;
    double redlineRPM;
    double inertia;
    double frictionCoeff;
};

class Engine {
public:
    Engine(const EngineSpecs& specs, TorqueCurve curve);

    void update(double dt, double throttleInput, double loadTorque, double vehicleSpeedMps);

    // Getters (for terminal output)
    double getRPM() const {return rpm;}
    double getTorque() const {return engineTorque;}
    double getPowerKW() const {return enginePowerKW;}

    const FuelTank& getFuelTank() const {return fuelTank;}
    const ConsumptionStats& getConsumption() const {return consumption;}

    double getInstantConsumption() const {return instantLper100km;}
    bool isRunning() const {return engineRunning;}

private:
    // Engine state
    double rpm = 0.0;
    double omega = 0.0;         // rad/s
    double engineTorque = 0.0;
    double enginePowerKW = 0.0;

    bool engineRunning = true;

    EngineSpecs specs;

    // Fuel system
    FuelTank fuelTank;
    ConsumptionStats consumption;

    double instantLper100km = 0.0;

    TorqueCurve torqueCurve;
    ECU ecu;
    ECUState ecuState;
};