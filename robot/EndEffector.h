//
// Created by ceyx on 12/29/24.
//

#ifndef ENDEFFECTOR_H
#define ENDEFFECTOR_H

#include "hardware/Motor.h"
#include "hardware/Coms.h"
#include <memory>
#include <utility>

namespace robot {
    class EndEffector {
    public:
        explicit EndEffector(hardware::Coms &coms, const std::vector<uint8_t> &ids);

        void update_feedback();

        void setup() const;

        void shutdown() const;

    protected:
        hardware::Coms &coms_;
        std::vector<std::unique_ptr<hardware::Motor> > motors_;

        void enable_motors() const;

        void disable_motors() const;

        void send_positions(const std::vector<double_t> &positions) const;

        void send_velocities(const std::vector<double_t> &velocities) const;

        void go_home() const;
    };
} // robot

#endif //ENDEFFECTOR_H
