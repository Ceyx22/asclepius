//
// Created by ceyx on 12/14/24.
//
#define FMT_HEADER_ONLY
#include <iostream>
// #include <fmt/format.h>

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "motor.h"
#include "coms.h"


namespace hardware {
    void motor::enable_torque(coms connection_) const {
        if (!connection_.write1ByteTxRx(id_, ADDR_TORQUE_ENABLE, ENABLE)) {
            spdlog::error("Failed to enable Torque for motor {} ", id_);
            // TODO: add behavior for failed connection
        }
        spdlog::info("Enabled Torque for motor {} ", id_);
    };

    void motor::disable_torque(coms connection_) const {
        if (!connection_.write1ByteTxRx(id_, ADDR_TORQUE_ENABLE, DISABLE)) {
            spdlog::error("Failed to disable Torque for motor {}", id_);
            // TODO: add behavior for failed connection
        }
        spdlog::info("Disabled Torque for motor {}", id_);
    };

    double_t motor::get_position_error() const {
        spdlog::info("Getting position error for motor {}", id_);
        spdlog::info("Commanded Position {}", commanded_position_);
        spdlog::info("Actual Position {}", actual_position_);
        spdlog::info("Error {}", commanded_position_ - actual_position_);
        return commanded_position_ - actual_position_;
    };

    double_t motor::get_velocity_error() const {
        return commanded_velocity_ - actual_velocity_;
    };

    /*
     *  takes in radians and converts to motor position before sending out
    *   interpolates to find the correct motor value
    *   TODO: Take into account offset
    */
    void motor::set_commanded_position(const double_t commanded_position, coms connection_) {
        commanded_position_ = commanded_position;
        const int position_send = MIN_MOTOR_VALUE + (commanded_position - MIN_MOTOR_VALUE) * ((
                                          MAX_MOTOR_VALUE - MIN_MOTOR_VALUE) / (MAX_RADIANS - MIN_RADIANS));
        spdlog::info("Setting commanded position to {}", position_send);

        connection_.write2ByteTxRx(id_, ADDR_GOAL_POSITION, position_send);
    };

    void motor::set_commanded_velocity(const double_t commanded_velocity, coms connection_) {
        commanded_velocity_ = commanded_velocity;
        const int velocity_send = commanded_velocity * RADS_PER_SEC_TO_RPM;
        connection_.write2ByteTxRx(id_, ADDR_GOAL_POSITION, velocity_send);
    };

    // TODO: clean up code
    void motor::update_feedback(coms connection_) {
        bool is_success_pos = false;
        bool is_success_vel = false;
        uint16_t motor_byte_position_ = 0;
        uint16_t motor_byte_velocity_ = 0;
        is_success_pos = connection_.read2ByteTxRx(id_, ADDR_PRESENT_POSITION, &motor_byte_position_);
        is_success_vel = connection_.read2ByteTxRx(id_, ADDR_PRESENT_SPEED, &motor_byte_velocity_);
        spdlog::info("Updating feedback for motor {}", id_);
        spdlog::info("Position {}", motor_byte_position_);
        spdlog::info("Velocity {}", motor_byte_velocity_);
        if (is_success_pos) {
            //TODO: add back offset
            actual_position_ = MIN_RADIANS + (motor_byte_position_ - MIN_MOTOR_VALUE) * (
                                   (MAX_RADIANS - MIN_RADIANS) / (MAX_MOTOR_VALUE - MIN_MOTOR_VALUE));
            spdlog::info("Updating motor position to {}", actual_position_);
        }
        if (is_success_vel) {
            double rpm;
            if (motor_byte_velocity_ == MIN_CCW_MOTOR_RPM || motor_byte_velocity_ == MIN_CW_MOTOR_RPM) {
                actual_velocity_ = 0.0;
            } else if (motor_byte_velocity_ <= MAX_CCW_MOTOR_RPM) {
                rpm = MIN_RPM + (motor_byte_velocity_ - MIN_CCW_MOTOR_RPM) * (
                          (MAX_RPM - MIN_RPM) / (MAX_CCW_MOTOR_RPM - MIN_CCW_MOTOR_RPM));
                actual_velocity_ = 60 * rpm / (2 * M_PI);
            } else if (MIN_CW_MOTOR_RPM < MAX_CW_MOTOR_RPM) {
                rpm = -MIN_RPM + (motor_byte_velocity_ - MIN_CW_MOTOR_RPM) * (
                          (MAX_RPM - MIN_RPM) / (MAX_CW_MOTOR_RPM - MIN_CW_MOTOR_RPM));
                actual_velocity_ = (60 * rpm) / (2 * M_PI);
            }
        }
    };
}
