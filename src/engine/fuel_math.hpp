#pragma once
#include "engine_constants.hpp"

// kg/s from power
inline double fuelFlowKgPerSec(double enginePowerKW) {
    return (enginePowerKW * BSFC_GASOLINE) /  3600.0;
}

// L/s from kg/s
inline double fuelFlowLitersPerSec(double fuelFlowKgps) {
    return fuelFlowKgps / GASOlINE_DENSITY;
}

// L/100km
inline double instantConsumptionLper100km(
    double fuelFlowLps,
    double vehicleSpeedKmh
) {
    if (vehicleSpeedKmh < 1.0)
        return 0.0;

    return (fuelFlowLps * 3600.0 / vehicleSpeedKmh) * 100.0;
}