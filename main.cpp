#include <iostream>
#include <chrono>
#include <thread>
#include "hardware/coms.h"
#include "hardware/motor.h"
using namespace std::this_thread;
using namespace std::chrono_literals;

int main() {
    const auto port = "/dev/ttyUSB0";
    constexpr auto baud_rate = 1000000;
    auto main_coms = hardware::coms(port, baud_rate);
    // hardware::coms main_coms;
    main_coms.connect();
    auto motor_a = hardware::motor(7, 0);
    motor_a.enable_torque(main_coms);
    // motor_a.update_feedback(main_coms);
    motor_a.set_commanded_position(2.61799, main_coms);
    // sleep_for(10s);

    motor_a.update_feedback(main_coms);
    auto e = motor_a.get_position_error();
    std::cout << e << std::endl;

    main_coms.disconnect();

    return 0;
}





