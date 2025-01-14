#define FMT_HEADER_ONLY


#include <chrono>
#include <memory>
#include <thread>


#include "LoggerManager.h"
#include "Coms.h"
#include "Motor.h"
#include "EndEffector.h"
#include "TrajectoryController.h"

int main() {
    const auto logger = util::LoggerManager::getLogger();
    bool done = false;
    logger->info("Starting...");
    // starting at 0 errors out
    double_t t = 0.01;
    // estimated from runtime
    double_t dt = 0.12;
    const auto port = "/dev/ttyUSB0";
    constexpr auto baud_rate = 1000000;
    std::shared_ptr<hardware::Coms> main_coms = std::make_shared<hardware::Coms>(port, baud_rate);
    std::vector<u_int8_t> ids = {7, 9, 11, 12}; // 10, motor 10 dead?
    auto rbot = robot::EndEffector(main_coms, ids);
    rbot.setup();

    std::vector<double_t> state_a = {2.62, 2.62, 2.62, 2.62};
    std::vector<double_t> state_b = {0.0, 0.0, 0.0, 0.0};
    auto traj_a = robot::TrajectoryController(state_a, state_b, 5.0);
    auto traj_b = robot::TrajectoryController(state_b, state_a, 10.0);
    std::tuple<std::vector<double_t>, std::vector<double_t> > curr_traj;


    while (!done) {
        std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
        // rbot.update_feedback();
        if (t < 5) {
            curr_traj = traj_a.calcTrajectory(t, dt);
            //invert to tuple inside vector
            util::LoggerManager::getLogger()->info("Trajectory A Position: {}", std::get<0>(curr_traj)[0]);
            util::LoggerManager::getLogger()->info("Trajectory A Velocity: {}", std::get<0>(curr_traj)[1]);
            rbot.send_commands(std::get<0>(curr_traj), std::get<1>(curr_traj));
        }
        if (t > 5 && t < 10) {
            curr_traj = traj_b.calcTrajectory(t - 5, dt);
            util::LoggerManager::getLogger()->info("Trajectory B Position: {}", std::get<0>(curr_traj)[0]);
            util::LoggerManager::getLogger()->info("Trajectory B Velocity: {}", std::get<0>(curr_traj)[1]);
            rbot.send_commands(std::get<0>(curr_traj), std::get<1>(curr_traj));
        }

        if (t > 10) {
            done = true;
        }

        std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
        dt = std::chrono::duration_cast<std::chrono::duration<double> >(end_time - start_time).count();
        util::LoggerManager::getLogger()->info("Elapsed time: {} s", dt);
        util::LoggerManager::getLogger()->info("Current time: {}", t);
        t = t + dt;
    }
    rbot.shutdown();


    return 0;
}





