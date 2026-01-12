#pragma once

struct VehicleState {
    double speed = 0.0; // m/s

    double speedKmh() const {
        return speed * 3.6;
    }
};