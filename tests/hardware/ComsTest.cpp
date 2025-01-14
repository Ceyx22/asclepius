//
// Created by ceyx on 1/11/25.
//
#include <gtest/gtest.h>
#include "Coms.h"

TEST(ComsTests, Initialization) {
    std::shared_ptr<hardware::Coms> main_coms = std::make_shared<hardware::Coms>("/dev/ttyUSB0", 1000000);

    EXPECT_TRUE(main_coms->connect());
}

TEST(ComsTests, SendMessage) {
    std::shared_ptr<hardware::Coms> main_coms = std::make_shared<hardware::Coms>("/dev/ttyUSB0", 1000000);
    bool result = false;
    result = main_coms->connect();
    EXPECT_TRUE(result);

    uint8_t value = 1;
    //enables torque
    result = main_coms->write1Byte(7, 24, value);
    EXPECT_TRUE(result);
}
