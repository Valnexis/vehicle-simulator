#pragma once

struct FuelTank {
    double capacityLiters;
    double currentLiters;

    FuelTank(double capacity = 50.0)
        : capacityLiters(capacity), currentLiters(capacity) {}

    bool isEmpty() const {
        return currentLiters <= 0.0;
    }

    void consume(double liters) {
        currentLiters -= liters;
        if (currentLiters <= 0.0)
            currentLiters = 0.0;
    }
};

struct ConsumptionStats {
    double totalFuelUsedLiters = 0.0;
    double totalDistanceKm = 0.0;

    double averageLper100km() const {
        if (totalDistanceKm <= 0.0)
            return 0.0;
        return (totalFuelUsedLiters / totalDistanceKm) * 100.0;
    }
};