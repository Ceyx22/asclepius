//
// Created by ceyx on 12/29/24.
//
#define FMT_HEADER_ONLY

#include "EndEffector.h"
#include "hardware/Coms.h"
#include "util/LoggerManager.h"
#include "util/MathUtil.h"

namespace robot {
    /*
     * Public
     */
    EndEffector::EndEffector(const std::shared_ptr<hardware::Coms> &coms,
                             const std::vector<uint8_t> &ids): coms_(coms) {
        coms_->connect();
        deadband_ = 0.01;
        motors_.reserve(ids.size());
        actual_positions_.reserve(ids.size());
        actual_velocities_.reserve(ids.size());
        home_positions_.reserve(ids.size());
        for (unsigned char id: ids) {
            util::LoggerManager::getLogger()->info("created motor {}", id);
            motors_.emplace_back(std::make_unique<hardware::Motor>(id, 0, coms_));
            actual_positions_.emplace_back(0.0);
            actual_velocities_.emplace_back(0.0);
            home_positions_.emplace_back(0.0);
        }
    }

    void EndEffector::send_commands(const std::vector<double_t> &positions,
                                    const std::vector<double_t> &velocities) const {
        for (long unsigned int i = 0; i < motors_.size(); ++i) {
            // util::LoggerManager::getLogger()->info("Sending command {}: p:{} v:{}`", i, positions[i], velocities[i]);
            motors_[i]->set_commanded_position(positions[i]);
            motors_[i]->set_commanded_velocity(velocities[i]);
        }
    }

    void EndEffector::update_feedback() {
        for (long unsigned int i = 0; i < motors_.size(); ++i) {
            actual_positions_[i] = motors_[i]->get_feedback_position();
            actual_velocities_[i] = motors_[i]->get_feedback_velocity();
        }
    }

    void EndEffector::enable_motors() const {
        for (const auto &motor: motors_) {
            motor->enable_torque();
        }
    }

    void EndEffector::disable_motors() const {
        for (const auto &motor: motors_) {
            motor->disable_torque();
        }
    }

    // TODO: Add Trajectory Later
    void EndEffector::setup() {
        enable_motors();
        update_feedback();
        while (!all_motors_home_()) {
            update_feedback();
            send_commands(home_positions_, {0.0, 0.0, 0.0, 0.0});
        }
        util::LoggerManager::getLogger()->info("Finished setup() ");
    }

    void EndEffector::shutdown() const {
        disable_motors();
    }


    bool EndEffector::all_motors_home_() const {
        util::LoggerManager::getLogger()->info("Checking Motors ");
        for (long unsigned int i = 0; i < motors_.size(); ++i) {
            util::LoggerManager::getLogger()->info("home position {} ", home_positions_[i]);
            if (home_positions_[i] + deadband_ < actual_positions_[i]) {
                return false;
            }
        }
        return true;
    }
} // robot
