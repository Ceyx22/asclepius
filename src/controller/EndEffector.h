//
// Created by ceyx on 12/29/24.
//

#ifndef ENDEFFECTOR_H
#define ENDEFFECTOR_H

#include "Motor.h"
#include "Coms.h"
#include <memory>
#include <utility>

namespace robot {
    class EndEffector {
    public:
        explicit EndEffector(const std::shared_ptr<hardware::Coms> &coms, const std::vector<uint8_t> &ids);

        void update_feedback();

        void setup();

        void shutdown() const;

        void send_commands(const std::vector<double_t> &positions, const std::vector<double_t> &velocities) const;

    protected:
        std::shared_ptr<hardware::Coms> coms_;
        std::vector<std::unique_ptr<hardware::Motor> > motors_;
        std::vector<double_t> home_positions_;
        std::vector<double_t> actual_positions_;
        std::vector<double_t> actual_velocities_;
        double_t deadband_;

        void enable_motors() const;

        void disable_motors() const;

        [[nodiscard]] bool all_motors_home_() const;
    };
} // robot

#endif //ENDEFFECTOR_H
