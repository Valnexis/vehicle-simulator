#pragma once
#include <vector>
#include <utility>
#include <algorithm>

class TorqueCurve {
public:
    // (rpm, torqueNm)
    using Point = std::pair<double, double>;

    TorqueCurve(std::vector<Point> points)
        : curve(std::move(points)) {
        std::sort(curve.begin(), curve.end());
    }

    double getTorque(double rpm) const {
        if (curve.empty())
            return 0.0;

        if (rpm <= curve.front().first)
            return curve.front().second;

        if (rpm >= curve.back().first)
            return curve.back().second;

        for (size_t i = 0; i < curve.size() - 1; ++i) {
            const auto& [rpm1, tq1] = curve[i];
            const auto& [rpm2, tq2] = curve[i + 1];

            if (rpm >= rpm1 && rpm <= rpm2) {
                double t = (rpm - rpm1) / (rpm2 - rpm1);
                return tq1 + t * (tq2 - tq1);
            }
        }

        return 0.0;
    }

private:
    std::vector<Point> curve;
};