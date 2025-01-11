//
// Created by ceyx on 12/14/24.
//

#ifndef MOTOR_H
#define MOTOR_H

#include "Coms.h"

#include <dynamixel_sdk/dynamixel_sdk.h>
#include <cmath>
#include <cstdint>
#include <memory>


namespace hardware {
    class Motor {
    protected:
        uint8_t id_{};
        // offset is in radians
        double_t offset_{};

        uint8_t home_byte_position{};

        // between 0 and 1023
        uint16_t motor_byte_position_{};
        uint16_t motor_byte_velocity_{};
        double_t motor_rpm_{};

        uint16_t motor_byte_position_command_{};
        uint16_t motor_byte_rpm_command_{};

        std::shared_ptr<Coms> connection_;

    public:
        explicit Motor(uint8_t id, double_t offset, std::shared_ptr<Coms> coms);

        void enable_torque() const;

        void disable_torque() const;

        void set_commanded_position(double_t commanded_position);

        void set_commanded_velocity(double_t commanded_velocity);

        double_t get_feedback_position();

        double_t get_feedback_velocity();
    };
} // namespace hardware

#endif // MOTOR_H
