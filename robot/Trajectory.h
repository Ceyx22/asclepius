//
// Created by ceyx on 1/3/25.
//

#ifndef TRAJECTORY_H
#define TRAJECTORY_H
#include <cmath>
#include <vector>

namespace robot {
    class Trajectory {
    public:
        explicit Trajectory(const std::vector<double_t> &desired_angles);

        std::tuple<std::vector<double_t>, std::vector<double_t> > calcTrajectory(double_t t, double_t dt);

    protected:
        std::vector<double_t> q_;
        std::vector<double_t> dq_;

        std::vector<double_t> q_0_;
        std::vector<double_t> dq_0_;
        std::vector<double_t> desired_q_;
    };
}


#endif //TRAJECTORY_H
