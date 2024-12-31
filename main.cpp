#define FMT_HEADER_ONLY


#include <chrono>
#include <thread>

#include "hardware/Coms.h"
#include "hardware/Motor.h"
#include "util/LoggerManager.h"
#include "robot/EndEffector.h"
#include "util/Scheduler.h"

int main() {
    const auto logger = util::LoggerManager::getLogger();
    double_t dt = 0.000612;
    logger->info("Starting...");
    const auto port = "/dev/ttyUSB0";
    constexpr auto baud_rate = 1000000;
    auto main_coms = hardware::Coms(port, baud_rate);
    std::vector<u_int8_t> ids = {7, 9, 10, 11};
    auto rbot = robot::EndEffector(main_coms, ids);
    rbot.setup();
    util::Scheduler scheduler(1);
    scheduler.add_task([&rbot]() {
        rbot.update_feedback();
    });
    std::this_thread::sleep_for(std::chrono::seconds(2));
    rbot.shutdown();
    return 0;
}





