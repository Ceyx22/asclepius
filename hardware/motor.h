//
// Created by ceyx on 12/14/24.
//

#ifndef MOTOR_H
#define MOTOR_H

#include "coms.h"

#include <cmath>
#include <cstdint>
#include <dynamixel_sdk/dynamixel_sdk.h>

namespace hardware {
    class motor {
    protected:
        // EEPROM AREA - Stored permanently and requires a reboot to take effect
        const uint8_t ADDR_MODEL_NUMBER_L = 0;
        const uint8_t ADDR_MODEL_NUMBER_H = 1;
        const uint8_t ADDR_FIRMWARE_VERSION = 2;
        const uint8_t ADDR_ID = 3;
        const uint8_t ADDR_BAUD_RATE = 4;
        const uint8_t ADDR_RETURN_DELAY_TIME = 5;
        const uint8_t ADDR_CW_ANGLE_LIMIT = 6;
        const uint8_t ADDR_CCW_ANGLE_LIMIT = 8;
        const uint8_t ADDR_DRIVE_MODE = 10;
        const uint8_t ADDR_LIMIT_TEMPERATURE = 11;
        const uint8_t ADDR_LOW_VOLTAGE_LIMIT = 12;
        const uint8_t ADDR_HIGH_VOLTAGE_LIMIT = 13;
        const uint8_t ADDR_MAX_TORQUE = 14;
        const uint8_t ADDR_STATUS_RETURN_LEVEL = 16;
        const uint8_t ADDR_ALARM_LED = 17;
        const uint8_t ADDR_ALARM_SHUTDOWN = 18;

        // RAM AREA - Temporary and can change during runtime
        const uint8_t ADDR_TORQUE_ENABLE = 24;
        const uint8_t ADDR_LED = 25;
        const uint8_t ADDR_CW_COMPLIANCE_MARGIN = 26;
        const uint8_t ADDR_CCW_COMPLIANCE_MARGIN = 27;
        const uint8_t ADDR_CW_COMPLIANCE_SLOPE = 28;
        const uint8_t ADDR_CCW_COMPLIANCE_SLOPE = 29;
        const uint8_t ADDR_GOAL_POSITION = 30;
        const uint8_t ADDR_MOVING_SPEED = 32;
        const uint8_t ADDR_TORQUE_LIMIT = 34;
        const uint8_t ADDR_PRESENT_POSITION = 36;
        const uint8_t ADDR_PRESENT_SPEED = 38;
        const uint8_t ADDR_PRESENT_LOAD = 40;
        const uint8_t ADDR_PRESENT_VOLTAGE = 42;
        const uint8_t ADDR_PRESENT_TEMPERATURE = 43;
        const uint8_t ADDR_REGISTERED_INSTRUCTION = 44;
        const uint8_t ADDR_MOVING = 46;
        const uint8_t ADDR_LOCK = 47;
        const uint8_t ADDR_PUNCH = 48;

        const uint8_t ENABLE = 1;
        const uint8_t DISABLE = 0;

        const uint16_t MAX_MOTOR_VALUE = 1023;
        const uint16_t MIN_MOTOR_VALUE = 0;
        const double MAX_RADIANS = 5.23089680507;
        const double MIN_RADIANS = 0;
        const double RADS_PER_SEC_TO_RPM = 9.549297;
        const double MAX_RPM = 59.0;
        const double MIN_RPM = 0;
        const uint16_t MAX_CCW_MOTOR_RPM = 1023;
        const uint16_t MIN_CCW_MOTOR_RPM = 0;
        const uint16_t MAX_CW_MOTOR_RPM = 2047;
        const uint16_t MIN_CW_MOTOR_RPM = 1024;


        const uint8_t id_{};
        // offset is in radians
        const double_t offset_{};

        // between 0 and 1023
        // uint16_t motor_byte_position_{};
        // uint16_t motor_byte_velocity_{};

        // radians
        double_t actual_position_{};
        double_t actual_velocity_{};
        double_t commanded_position_{};
        double_t commanded_velocity_{};

    public:
        explicit motor(const uint8_t id, const uint16_t offset)
            : id_(id), offset_(offset) {
        };

        void enable_torque(coms connection_) const;

        void disable_torque(coms connection_) const;

        [[nodiscard]] double_t get_position_error() const;

        [[nodiscard]] double_t get_velocity_error() const;

        void set_commanded_position(double_t commanded_position, coms connection_);

        void set_commanded_velocity(double_t commanded_velocity, coms connection_);

        void update_feedback(coms connection_);
    };
} // namespace hardware

#endif // MOTOR_H
