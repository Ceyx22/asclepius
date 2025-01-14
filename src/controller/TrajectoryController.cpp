//
// Created by ceyx on 1/3/25.
//

#include "TrajectoryController.h"

#include <tuple>

#include "MathUtil.h"

namespace robot {
    TrajectoryController::TrajectoryController(const std::vector<double_t> &desired_angles, const std::vector<double_t> &start_position,
                           const double_t end_time) {
        desired_q_ = desired_angles;
        q_0_ = start_position;
        end_time_ = end_time;
        // copy?
        q_ = std::vector<double_t>(desired_angles.size(), 0.0);
        dq_ = std::vector<double_t>(desired_angles.size(), 0.0);
    }

    std::tuple<std::vector<double_t>, std::vector<double_t> >
    TrajectoryController::calcTrajectory(const double_t t, double_t dt) {
        for (unsigned int i = 0; i < q_.size(); i++) {
            std::tuple<double_t, double_t> temp = util::cubic_spline(t, end_time_, q_0_[i], desired_q_[i], 0.0, 0.0);
            q_[i] = std::get<0>(temp);
            dq_[i] = std::get<1>(temp);
        }

        return std::make_tuple(q_, dq_);
    }
}
