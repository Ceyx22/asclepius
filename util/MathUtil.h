//
// Created by ceyx on 12/31/24.
//

#ifndef MATHUTIL_H
#define MATHUTIL_H
#include <cmath>
#include <vector>


namespace util {
    std::tuple<double_t, double_t> cubic_spline(double_t t, double_t T, double_t p0, double_t pf, double_t v0,
                                                double_t vf);

    std::tuple<double_t, double_t> quintic_spline(double_t t, double_t T, double_t p0, double_t pf, double_t v0,
                                                  double_t vf, double_t a0,
                                                  double_t af);

    double_t interpolate(double_t x1, double_t y1, double_t x2, double_t y2, double_t input);

    double_t rpm_to_rad_sec(double_t rpm);
} // util

#endif //MATHUTIL_H
