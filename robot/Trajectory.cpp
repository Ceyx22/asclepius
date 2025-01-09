//
// Created by ceyx on 1/3/25.
//

#include "Trajectory.h"

#include <tuple>

#include "util/MathUtil.h"

namespace robot {
    Trajectory::Trajectory(const std::vector<double_t> &desired_angles) {
        desired_q_ = desired_angles;
        q_0_ = std::vector<double_t>(desired_angles.size(), 0.0);
        dq_0_ = std::vector<double_t>(desired_angles.size(), 0.0);
        q_ = std::vector<double_t>(desired_angles.size(), 0.0);
        dq_ = std::vector<double_t>(desired_angles.size(), 0.0);
    }

    std::tuple<std::vector<double_t>, std::vector<double_t> >
    Trajectory::calcTrajectory(const double_t t, double_t dt) {
        for (unsigned int i = 0; i < q_.size(); i++) {
            std::tuple<double_t, double_t> temp = util::cubic_spline(t, 5.0, q_0_[i], desired_q_[i], 0.0, 0.0);
            q_[i] = std::get<0>(temp);
            dq_[i] = std::get<1>(temp);
        }

        return std::make_tuple(q_, dq_);
    }
}
