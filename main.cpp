#define FMT_HEADER_ONLY


#include <chrono>
#include <thread>

#include "hardware/Coms.h"
#include "hardware/Motor.h"
#include "util/LoggerManager.h"
using namespace std::this_thread;
using namespace std::chrono_literals;

int main() {
    const auto logger = util::LoggerManager::getLogger();
    logger->info("Starting...");
    const auto port = "/dev/ttyUSB0";
    constexpr auto baud_rate = 1000000;
    auto main_coms = hardware::Coms(port, baud_rate);
    // hardware::coms main_coms;
    main_coms.connect();
    auto motor_a = hardware::Motor(7, 0);
    motor_a.enable_torque(main_coms);
    motor_a.set_commanded_position(2.61799, main_coms);
    sleep_for(1s);

    motor_a.update_feedback(main_coms);
    sleep_for(10ns);
    auto e = motor_a.get_position_error();

    main_coms.disconnect();

    return 0;
}





