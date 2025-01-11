//
// Created by ceyx on 12/31/24.
//

#include "MathUtil.h"

#include <tuple>

namespace util {
    std::tuple<double_t, double_t> cubic_spline(const double_t t, const double_t T, const double_t p0,
                                                const double_t pf,
                                                const double_t v0, const double_t vf) {
        const double_t T2 = T * T;
        const double_t T3 = T2 * T;

        const double_t a = p0;
        const double_t b = v0;
        const double_t c = 3 * (pf - p0) / T2 - vf / T - 2 * v0 / T;
        const double_t d = -2 * (pf - p0) / T3 + vf / T2 + v0 / T2;

        const double_t p = a + b * t + c * t * t + d * t * t * t;
        const double_t v = b + 2 * c * t + 3 * d * t * t;

        return std::make_tuple(p, v);
    }

    std::tuple<double_t, double_t> quintic_spline(const double_t t, const double_t T, const double_t p0,
                                                  const double_t pf, const double_t v0, const double_t vf,
                                                  const double_t a0, const double_t af) {
        const double_t T2 = T * T;
        const double_t T3 = T2 * T;
        const double_t T4 = T3 * T;
        const double_t T5 = T4 * T;

        const double_t a = p0;
        const double_t b = v0;
        const double_t c = a0;
        const double_t d = (10 * (pf - p0) / T3) - (6 * v0 / T2) - (3 * a0 / T) - (4 * vf / T2) + (0.5 * af / T);
        const double_t e = (-15 * (pf - p0) / T4) + (8 * v0 / T3) + (3 * a0 / T2) + (7 * vf / T3) - (af / T2);
        const double_t f = (6 * (pf - p0) / T5) - (3 * v0 / T4) - (a0 / T3) - (3 * vf / T4) + (0.5 * af / T3);

        const double_t t2 = t * t;
        const double_t t3 = t2 * t;
        const double_t t4 = t3 * t;
        const double_t t5 = t4 * t;

        const double_t p = a + b * t + c * t2 + d * t3 + e * t4 + f * t5;
        const double_t v = b + 2 * c * t + 3 * d * t2 + 4 * e * t3 + 5 * f * t4;

        return std::make_tuple(p, v);
    }


    double_t interpolate(const double_t x1, const double_t y1, const double_t x2, const double_t y2,
                         const double_t input) {
        return y1 + (input - x1) * ((y2 - y1) / (x2 - x1));
    }

    double_t rpm_to_rad_sec(const double_t rpm) {
        return 60 * rpm / (2 * M_PI);
    }

    double_t rad_sec_to_rpm(const double_t rad) {
        return rad * (60 / (2 * M_PI));
    }

    // double_t calc_max_accel(const double_t max_torque, const double_t moment_of_inertia) {
    //     return max_torque / moment_of_inertia;
    // }
} // util
