//
// Created by ceyx on 12/29/24.
//

#include "EndEffector.h"
#include "Coms.h"

namespace robot {
    EndEffector::EndEffector(hardware::Coms &coms, const std::vector<uint8_t> &ids): coms_(coms) {
        coms_.connect();
        for (int id: ids) {
            motors_.emplace_back(std::make_unique<hardware::Motor>(id, 0));
        }
    }

    void EndEffector::enable_motors() const {
        for (const auto &motor: motors_) {
            motor->enable_torque(coms_);
        }
    }

    void EndEffector::disable_motors() const {
        for (const auto &motor: motors_) {
            motor->disable_torque(coms_);
        }
    }

    void EndEffector::shutdown() const {
        disable_motors();
    }


    void EndEffector::send_positions(const std::vector<double_t> &positions) const {
        for (long unsigned int i = 0; i < positions.size(); ++i) {
            motors_[i]->set_commanded_position(positions[i], coms_);
        }
    }

    void EndEffector::send_velocities(const std::vector<double_t> &velocities) const {
        for (long unsigned int i = 0; i < velocities.size(); ++i) {
            motors_[i]->set_commanded_position(velocities[i], coms_);
        }
    }

    void EndEffector::update_feedback() {
        for (const auto &motor: motors_) {
            motor->update_feedback(coms_);
        }
    }

    void EndEffector::go_home() const {
        for (const auto &motor: motors_) {
            motor->go_home(coms_);
        }
    }

    void EndEffector::setup() const {
        enable_motors();
        go_home();
    }
} // robot
