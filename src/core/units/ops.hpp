#pragma once
#include "seconds.hpp"
#include "meters.hpp"
#include "meters_per_second.hpp"
#include "meters_per_second2.hpp"

namespace units {
//scalar ops
constexpr Meters operator+(Meters a, Meters b) {return Meters{a.value + b.value};}
constexpr Meters operator-(Meters a, Meters b) {return Meters{a.value - b.value};}

constexpr MetersPerSecond operator+(MetersPerSecond a, MetersPerSecond b) {return MetersPerSecond{a.value + b.value};}
constexpr MetersPerSecond operator-(MetersPerSecond a, MetersPerSecond b) {return MetersPerSecond{a.value - b.value};}

constexpr MetersPerSecond2 operator+(MetersPerSecond2 a, MetersPerSecond2 b) {return MetersPerSecond2{a.value + b.value};}
constexpr MetersPerSecond2 operator-(MetersPerSecond2 a, MetersPerSecond2 b) {return MetersPerSecond2{a.value - b.value};}

constexpr Meters operator*(MetersPerSecond v, Seconds dt) {return Meters{v.value * dt.value};}
constexpr MetersPerSecond operator*(MetersPerSecond2 a, Seconds dt) {return MetersPerSecond{a.value * dt.value};}

constexpr MetersPerSecond operator*(MetersPerSecond v, double s) {return MetersPerSecond{v.value * s};}
constexpr MetersPerSecond2 operator*(MetersPerSecond2 a, double s) {return MetersPerSecond2{a.value * s};}
}