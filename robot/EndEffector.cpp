//
// Created by ceyx on 12/29/24.
//
#define FMT_HEADER_ONLY

#include "EndEffector.h"
#include "Coms.h"
#include "util/LoggerManager.h"
#include "util/MathUtil.h"

namespace robot {
    /*
     * Public
     */
    EndEffector::EndEffector(hardware::Coms &coms, const std::vector<uint8_t> &ids): coms_(coms) {
        coms_.connect();
        deadband_ = 0.01;
        for (uint8_t id: ids) {
            util::LoggerManager::getLogger()->info("created motor {}", id);
            motors_.emplace_back(std::make_unique<hardware::Motor>(id, 0));
            actual_positions_.emplace_back(0.0);
            actual_velocities_.emplace_back(0.0);
            home_positions_.emplace_back(0.0);
        }
    }

    void EndEffector::send_commands(const std::vector<double_t> &positions,
                                    const std::vector<double_t> &velocities) const {
        for (long unsigned int i = 0; i < motors_.size(); ++i) {
            motors_[i]->set_commanded_position(positions[i], coms_);
            // motors_[i]->set_commanded_velocity(velocities[i], coms_);
        }
    }

    void EndEffector::update_feedback() {
        for (long unsigned int i = 0; i < motors_.size(); ++i) {
            actual_positions_[i] = motors_[i]->get_feedback_position(coms_);
            actual_velocities_[i] = motors_[i]->get_feedback_velocity(coms_);
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

    // TODO: Add Trajectory Later
    void EndEffector::setup() {
        enable_motors();
        update_feedback();
        // while (!all_motors_home_()) {
        //     update_feedback();
        //     send_commands(home_positions_, {0.0, 0.0, 0.0, 0.0});
        // }
        util::LoggerManager::getLogger()->info("Finished setup() ");
    }

    void EndEffector::shutdown() const {
        disable_motors();
    }


    bool EndEffector::all_motors_home_() const {
        util::LoggerManager::getLogger()->info("Checking Motors ");
        for (long unsigned int i = 0; i < motors_.size(); ++i) {
            if (home_positions_[i] + deadband_ < actual_positions_[i]) {
                return false;
            }
        }
        return true;
    }
} // robot
