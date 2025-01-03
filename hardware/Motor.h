//
// Created by ceyx on 12/14/24.
//

#ifndef MOTOR_H
#define MOTOR_H

#include "Coms.h"
#include "hardware/Constants.h"

#include <cmath>
#include <cstdint>
#include <dynamixel_sdk/dynamixel_sdk.h>

namespace hardware {
    class Motor {
    protected:
        uint8_t id_{};
        // offset is in radians
        double_t offset_{};

        uint8_t home_byte_position = 0;
        double_t home_position_ = 0.0;

        // between 0 and 1023
        uint16_t motor_byte_position_{};
        uint16_t motor_byte_velocity_{};
        double_t motor_rpm_{};

        uint16_t motor_byte_position_command_{};
        uint16_t motor_byte_rpm_command_{};

        // radians
        double_t actual_position_{};
        double_t actual_velocity_{};
        double_t commanded_position_{};
        double_t commanded_velocity_{};

    public:
        explicit Motor(uint8_t id, double_t offset);

        void enable_torque(Coms connection_) const;

        void disable_torque(Coms connection_) const;

        [[nodiscard]] double_t get_position_error() const;

        [[nodiscard]] double_t get_velocity_error() const;

        void set_commanded_position(double_t commanded_position, Coms connection_);

        void set_commanded_velocity(double_t commanded_velocity, Coms connection_);

        void update_feedback(Coms connection_);

        void go_home(Coms connection_) const;
    };

    double_t interpolate(double_t x1, double_t y1, double_t x2, double_t y2, double_t input);

    double_t rpm_to_rad_sec(double_t rpm);
} // namespace hardware

#endif // MOTOR_H
