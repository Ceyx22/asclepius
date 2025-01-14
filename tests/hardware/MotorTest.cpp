//
// Created by ceyx on 1/11/25.
//
#include <gtest/gtest.h>
#include "Coms.h"
#include "Motor.h"


class MotorIntegrationTest : public ::testing::Test {
protected:
    std::shared_ptr<hardware::Coms> coms;
    std::shared_ptr<hardware::Motor> motor;

    void SetUp() override {
        coms = std::make_shared<hardware::Coms>("/dev/ttyUSB0", 1000000);;
        ASSERT_TRUE(coms->connect()) << "Failed to connect to Dynamixel bus";

        motor = std::make_shared<hardware::Motor>(7, 0, coms);
    }

    void TearDown() override {
        // Disconnect and clean up
        coms->disconnect();
    }
};

TEST_F(MotorIntegrationTest, EnableAndDisableTorque) {
    motor->enable_torque();
    EXPECT_TRUE(motor->is_torque_enabled()) << "Failed to enable torque on motor";
    motor->disable_torque();
    EXPECT_FALSE(motor->is_torque_enabled()) << "Failed to disable torque on motor";
}

TEST_F(MotorIntegrationTest, SetAndGetPosition) {
    // middle position
    constexpr double_t goalPosition = 2.61799;
    EXPECT_TRUE(motor->set_commanded_position(goalPosition)) << "Failed to set motor position";
}

