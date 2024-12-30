//
// Created by ceyx on 12/14/24.
//
#define FMT_HEADER_ONLY

#include "util/LoggerManager.h"
#include "hardware/Motor.h"
#include "hardware/Coms.h"


namespace hardware {
    Motor::Motor(const uint8_t id, const double_t offset) {
        id_ = id;
        offset_ = offset;
    }

    void Motor::enable_torque(Coms connection_) const {
        if (!connection_.write1ByteTxRx(id_, ADDR_TORQUE_ENABLE, ENABLE)) {
            util::LoggerManager::getLogger()->error("Failed to enable Torque for motor {} ", id_);
            // TODO: add behavior for failed connection
        }
        util::LoggerManager::getLogger()->info("Enabled Torque for motor {} ", id_);
    };

    void Motor::disable_torque(Coms connection_) const {
        if (!connection_.write1ByteTxRx(id_, ADDR_TORQUE_ENABLE, DISABLE)) {
            util::LoggerManager::getLogger()->error("Failed to disable Torque for motor {}", id_);
            // TODO: add behavior for failed connection
        }
        util::LoggerManager::getLogger()->info("Disabled Torque for motor {}", id_);
    };

    double_t Motor::get_position_error() const {
        util::LoggerManager::getLogger()->info("Getting position error for motor {} error value {}", id_,
                                               commanded_position_ - actual_position_);
        return commanded_position_ - actual_position_;
    };

    double_t Motor::get_velocity_error() const {
        util::LoggerManager::getLogger()->info("Getting position error for motor {} error value {}", id_,
                                               commanded_velocity_ - actual_velocity_);
        return commanded_velocity_ - actual_velocity_;
    };

    /*
     *  takes in radians and converts to motor position before sending out
     *  interpolates to find the correct motor value
     *   TODO: Take into account offset
     */
    void Motor::set_commanded_position(const double_t commanded_position, Coms connection_) {
        commanded_position_ = commanded_position;
        motor_byte_position_command_ = static_cast<uint16_t>(interpolate(MIN_RADIANS, MIN_MOTOR_VALUE, MAX_RADIANS,
                                                                         MAX_MOTOR_VALUE,
                                                                         commanded_position));
        util::LoggerManager::getLogger()->info("Setting commanded position to {}", motor_byte_position_command_);

        connection_.write2ByteTxRx(id_, ADDR_GOAL_POSITION, motor_byte_position_command_);
    };

    void Motor::set_commanded_velocity(const double_t commanded_velocity, Coms connection_) {
        commanded_velocity_ = commanded_velocity;
        motor_byte_rpm_command_ = static_cast<uint16_t>(commanded_velocity * RADS_PER_SEC_TO_RPM);
        util::LoggerManager::getLogger()->info("Setting commanded velocity to {}", motor_byte_rpm_command_);
        connection_.write2ByteTxRx(id_, ADDR_GOAL_POSITION, motor_byte_rpm_command_);
    };

    // TODO: clean up code
    void Motor::update_feedback(Coms connection_) {
        util::LoggerManager::getLogger()->info("Updating feedback for motor {}", id_);

        if (connection_.read2ByteTxRx(id_, ADDR_PRESENT_POSITION, &motor_byte_position_)) {
            //TODO: add back offset
            util::LoggerManager::getLogger()->info("Position {}", motor_byte_position_);

            actual_position_ = interpolate(MIN_MOTOR_VALUE, MIN_RADIANS, MAX_MOTOR_VALUE, MAX_RADIANS,
                                           motor_byte_position_);
            util::LoggerManager::getLogger()->info("Updating motor position to {}", actual_position_);
        }
        if (connection_.read2ByteTxRx(id_, ADDR_PRESENT_SPEED, &motor_byte_velocity_)) {
            if (motor_byte_velocity_ == MIN_CCW_MOTOR_RPM || motor_byte_velocity_ == MIN_CW_MOTOR_RPM) {
                actual_velocity_ = 0.0;
            } else if (motor_byte_velocity_ <= MAX_CCW_MOTOR_RPM) {
                // might have to change if statements to add lower bound
                motor_rpm_ = interpolate(MIN_CCW_MOTOR_RPM, MIN_RPM, MAX_CCW_MOTOR_RPM, MAX_RPM, motor_byte_velocity_);
                actual_velocity_ = rpm_to_rad_sec(motor_rpm_);
            } else if (MIN_CW_MOTOR_RPM <= MAX_CW_MOTOR_RPM) {
                // might have to change if statements to add lower bound
                motor_rpm_ = -interpolate(MIN_CW_MOTOR_RPM, MIN_RPM, MAX_CW_MOTOR_RPM, MAX_RPM, motor_byte_velocity_);
                actual_velocity_ = rpm_to_rad_sec(motor_rpm_);
            }
            util::LoggerManager::getLogger()->info("Velocity {}", motor_byte_velocity_);
        }
    };

    double_t interpolate(const double_t x1, const double_t y1, const double_t x2, const double_t y2,
                         const double_t input) {
        return y1 + (input - x1) * ((y2 - y1) / (x2 - x1));
    }

    double_t rpm_to_rad_sec(const double_t rpm) {
        return 60 * rpm / (2 * M_PI);
    }
}
