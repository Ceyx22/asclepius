//
// Created by ceyx on 12/30/24.
//

#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <cstdint>


namespace constants {
    // EEPROM AREA - Stored permanently and requires a reboot to take effect
    enum EEPROMAddresses : uint8_t {
        MODEL_NUMBER_L = 0,
        MODEL_NUMBER_H = 1,
        FIRMWARE_VERSION = 2,
        ID = 3,
        BAUD_RATE = 4,
        RETURN_DELAY_TIME = 5,
        CW_ANGLE_LIMIT = 6,
        CCW_ANGLE_LIMIT = 8,
        DRIVE_MODE = 10,
        LIMIT_TEMPERATURE = 11,
        LOW_VOLTAGE_LIMIT = 12,
        HIGH_VOLTAGE_LIMIT = 13,
        MAX_TORQUE = 14,
        STATUS_RETURN_LEVEL = 16,
        ALARM_LED = 17,
        ALARM_SHUTDOWN = 18
    };

    // RAM AREA - Temporary and can change during runtime
    enum RAMAddresses : uint8_t {
        TORQUE_ENABLE = 24,
        LED = 25,
        CW_COMPLIANCE_MARGIN = 26,
        CCW_COMPLIANCE_MARGIN = 27,
        CW_COMPLIANCE_SLOPE = 28,
        CCW_COMPLIANCE_SLOPE = 29,
        GOAL_POSITION = 30,
        MOVING_SPEED = 32,
        TORQUE_LIMIT = 34,
        PRESENT_POSITION = 36,
        PRESENT_SPEED = 38,
        PRESENT_LOAD = 40,
        PRESENT_VOLTAGE = 42,
        PRESENT_TEMPERATURE = 43,
        REGISTERED_INSTRUCTION = 44,
        MOVING = 46,
        LOCK = 47,
        PUNCH = 48
    };

    constexpr uint8_t ENABLE = 1;
    constexpr uint8_t DISABLE = 0;


    constexpr uint16_t MAX_MOTOR_VALUE = 1023;
    constexpr uint16_t MIN_MOTOR_VALUE = 0;

    constexpr double MAX_RADIANS = 5.23089680507;
    constexpr double MIN_RADIANS = 0;
    constexpr double RADS_PER_SEC_TO_RPM = 9.549297;
    constexpr double MAX_RPM = 59.0;
    constexpr double MIN_RPM = 0;
    constexpr uint16_t MAX_CCW_MOTOR_RPM_BYTE = 1023;
    constexpr uint16_t MIN_CCW_MOTOR_RPM_BYTE = 0;
    constexpr uint16_t MAX_CW_MOTOR_RPM_BYTE = 2047;
    constexpr uint16_t MIN_CW_MOTOR_RPM_BYTE = 1024;
}
#endif //CONSTANTS_H
