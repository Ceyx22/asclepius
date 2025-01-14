//
// Created by ceyx on 1/12/25.
//

#ifndef MOCKCOMS_H
#define MOCKCOMS_H

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "ComsBase.h"

class MockComs final : public hardware::ComsBase {
public:
    MOCK_METHOD(bool, connect, (), (override));
    MOCK_METHOD(void, disconnect, (), (override));
    MOCK_METHOD(bool, write1Byte, (uint8_t id, uint16_t address, uint8_t value), (override));
    MOCK_METHOD(bool, write2Byte, (uint8_t id, uint16_t address, uint16_t value), (override));
    MOCK_METHOD(bool, read1Byte, (uint8_t id, uint16_t address, uint8_t *data), (override));
    MOCK_METHOD(bool, read2Byte, (uint8_t id, uint16_t address, uint16_t *data), (override));
};
#endif //MOCKCOMS_H
