#define FMT_HEADER_ONLY


#include <chrono>
#include <thread>

#include "hardware/Coms.h"
#include "hardware/Motor.h"
#include "util/LoggerManager.h"
#include "robot/EndEffector.h"
#include "robot/Trajectory.h"
#include "util/Scheduler.h"

int main() {
    const auto logger = util::LoggerManager::getLogger();
    bool done = false;
    logger->info("Starting...");
    // starting at 0 errors out
    double_t t = 0.01;
    double_t dt = 0.01;
    const auto port = "/dev/ttyUSB0";
    constexpr auto baud_rate = 1000000;
    auto main_coms = hardware::Coms(port, baud_rate);
    std::vector<u_int8_t> ids = {7, 9, 11, 12}; // 10, motor 10 dead?
    auto rbot = robot::EndEffector(main_coms, ids);
    rbot.setup();

    std::vector<double_t> state_a;
    state_a = {2.61799, 2.61799, 2.61799, 2.61799};
    std::vector<double_t> state_b = {0.0, 0.0, 0.0, 0.0};
    auto traj_a = robot::Trajectory(state_a);
    auto traj_b = robot::Trajectory(state_b);
    std::tuple<std::vector<double_t>, std::vector<double_t> > curr_traj;
    // std::chrono::milliseconds loop_interval(10);

    while (!done) {
        // double_t cycle_time = fmod(t, 5.0);
        util::LoggerManager::getLogger()->info("time {} ", t);
        //
        if (t < 5) {
            curr_traj = traj_a.calcTrajectory(t, dt);
            rbot.send_commands(std::get<0>(curr_traj), std::get<1>(curr_traj));
        }
        // if (t > 5 && t < 10) {
        //     curr_traj = traj_b.calcTrajectory(t - 5, dt);
        //     rbot.send_commands(std::get<0>(curr_traj), std::get<1>(curr_traj));
        // }

        if (t > 10) {
            done = true;
        }
        // std::this_thread::sleep_for(loop_interval);
        t = t + dt;
    }
    rbot.shutdown();
    // std::this_thread::sleep_for(std::chrono::seconds(2));


    return 0;
}





