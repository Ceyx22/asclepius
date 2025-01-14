//
// Created by ceyx on 1/3/25.
//

#ifndef TRAJECTORY_H
#define TRAJECTORY_H
#include <cmath>
#include <vector>

namespace robot {
    class TrajectoryController {
    public:
        explicit TrajectoryController(const std::vector<double_t> &desired_angles,
                                      const std::vector<double_t> &start_position, double_t end_time);

        // std::vector<std::tuple<double_t, double_t>>
        std::tuple<std::vector<double_t>, std::vector<double_t> > calcTrajectory(double_t t, double_t dt);

    protected:
        double_t end_time_{};
        std::vector<double_t> q_{};
        std::vector<double_t> dq_{};

        std::vector<double_t> q_0_{};
        std::vector<double_t> desired_q_;
    };
}


#endif //TRAJECTORY_H
