//
// Created by ceyx on 12/14/24.
//
#include <iostream>
#include <ostream>
#include <fmt/core.h>

#include "motor.h"
#include "coms.h"
#include "dynamixel_sdk/dynamixel_sdk.h"


namespace hardware {
    void motor::enable_torque(coms connection_) const {
        bool is_success = false;

        // Enable Torque of DYNAMIXEL
        is_success = connection_.write1ByteTxRx(id_, ADDR_TORQUE_ENABLE, ENABLE);

        if (!is_success) {
            // fmt::print("Failed to enable Torque for motor ");
            std::cout << "Failed to enable Torque for motor " << id_ << std::endl;
            // TODO: add behavior for failed connection
        }

        std::cout << "Torque enabled for motor " << id_ << std::endl;
    };

    void motor::disable_torque(coms connection_) const {
        bool is_success = false;
        // Disable Torque of DYNAMIXEL
        is_success = connection_.write1ByteTxRx(id_, ADDR_TORQUE_ENABLE, DISABLE);

        if (!is_success) {
            std::cout << "Failed to enable Torque for motor " << id_ << std::endl;
            // TODO: add behavior for failed connection
        }
        std::cout << "Torque enabled for motor " << id_ << std::endl;
    };

    double_t motor::get_position_error() const {
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
        std::cout << "Calculated position:" << position_send << std::endl;
        connection_.write2ByteTxRx(id_, ADDR_GOAL_POSITION, position_send);
    };

    void motor::set_commanded_velocity(const double_t commanded_velocity, coms connection_) {
        commanded_velocity_ = commanded_velocity;
        const int velocity_send = commanded_velocity * RADS_PER_SEC_TO_RPM;
        connection_.write2ByteTxRx(id_, ADDR_GOAL_POSITION, velocity_send);
    };

    void motor::update_feedback(coms connection_) {
        bool is_success_pos = false;
        bool is_success_vel = false;
        uint16_t motor_byte_position_ = 0;
        uint16_t motor_byte_velocity_ = 0;
        is_success_pos = connection_.read2ByteTxRx(id_, ADDR_PRESENT_POSITION, &motor_byte_position_);
        is_success_vel = connection_.read2ByteTxRx(id_, ADDR_PRESENT_SPEED, &motor_byte_velocity_);
        std::cout << "Read motor position:" << motor_byte_position_ << std::endl;
        std::cout << "Read motor velocity:" << motor_byte_velocity_ << std::endl;
        if (!is_success_pos) {
            //TODO: add back offset
            actual_position_ = MIN_RADIANS + (motor_byte_position_ - MIN_MOTOR_VALUE) * (
                                   (MAX_RADIANS - MIN_RADIANS) / (MAX_MOTOR_VALUE - MIN_MOTOR_VALUE));
        }
        if (!is_success_vel) {
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
