//
// Created by ceyx on 12/14/24.
//
#define FMT_HEADER_ONLY

#include "util/LoggerManager.h"
#include "hardware/Motor.h"
#include "hardware/Coms.h"
#include "hardware/Constants.h"
#include "util/MathUtil.h"

using namespace constants;

namespace hardware {
    Motor::Motor(const uint8_t id, const double_t offset) {
        id_ = id;
        offset_ = offset;
    }

    void Motor::enable_torque(Coms connection_) const {
        if (!connection_.write1ByteTxRx(id_, RAMAddresses::TORQUE_ENABLE, ENABLE)) {
            util::LoggerManager::getLogger()->error("Failed to enable Torque for motor {} ", id_);
        }
        util::LoggerManager::getLogger()->info("Enabled Torque for motor {} ", id_);
    };

    void Motor::disable_torque(Coms connection_) const {
        if (!connection_.write1ByteTxRx(id_, RAMAddresses::TORQUE_ENABLE, DISABLE)) {
            util::LoggerManager::getLogger()->error("Failed to disable Torque for motor {}", id_);
        }
        util::LoggerManager::getLogger()->info("Disabled Torque for motor {}", id_);
    };

    /*
     *  takes in radians and converts to motor position before sending out
     *  interpolates to find the correct motor value
     *   TODO: Take into account offset
     */
    void Motor::set_commanded_position(const double_t commanded_position, Coms connection_) {
        motor_byte_position_command_ = static_cast<uint16_t>(util::interpolate(
            MIN_RADIANS, MIN_MOTOR_VALUE, MAX_RADIANS,
            MAX_MOTOR_VALUE,
            commanded_position));

        connection_.write2ByteTxRx(id_, RAMAddresses::GOAL_POSITION, motor_byte_position_command_);
    };

    void Motor::set_commanded_velocity(const double_t commanded_velocity, Coms connection_) {
        motor_byte_rpm_command_ = static_cast<uint16_t>(util::interpolate(
            MIN_RPM, MIN_MOTOR_VALUE, MAX_RPM, MAX_MOTOR_VALUE,
            commanded_velocity * RADS_PER_SEC_TO_RPM));
        connection_.write2ByteTxRx(id_, RAMAddresses::MOVING_SPEED, motor_byte_rpm_command_);
    };


    double_t Motor::get_feedback_position(Coms connection_) {
        if (connection_.read2ByteTxRx(id_, RAMAddresses::PRESENT_POSITION, &motor_byte_position_)) {
            util::LoggerManager::getLogger()->info("Updating motor position to {}", motor_byte_position_);
        }
        return util::interpolate(MIN_MOTOR_VALUE, MIN_RADIANS, MAX_MOTOR_VALUE, MAX_RADIANS,
                                 motor_byte_position_);;
    }

    double_t Motor::get_feedback_velocity(Coms connection_) {
        if (connection_.read2ByteTxRx(id_, RAMAddresses::PRESENT_SPEED, &motor_byte_velocity_)) {
            if (motor_byte_velocity_ == MIN_CCW_MOTOR_RPM_BYTE || motor_byte_velocity_ == MIN_CW_MOTOR_RPM_BYTE) {
                motor_rpm_ = 0.0;
            } else if (motor_byte_velocity_ <= MAX_CCW_MOTOR_RPM_BYTE) {
                motor_rpm_ = util::interpolate(MIN_CCW_MOTOR_RPM_BYTE, MIN_RPM, MAX_CCW_MOTOR_RPM_BYTE, MAX_RPM,
                                               motor_byte_velocity_);
            } else if (motor_byte_velocity_ <= MAX_CW_MOTOR_RPM_BYTE) {
                motor_rpm_ = -util::interpolate(MIN_CW_MOTOR_RPM_BYTE, MIN_RPM, MAX_CW_MOTOR_RPM_BYTE, MAX_RPM,
                                                motor_byte_velocity_);
            }
        }
        return util::rpm_to_rad_sec(motor_rpm_);
    }
}
