//
// Created by ceyx on 1/12/25.
//

#ifndef COMSBASE_H
#define COMSBASE_H
#include <cstdint>

namespace hardware {
    class ComsBase {
    public:
        virtual ~ComsBase() = default;

        virtual bool connect() = 0;

        virtual void disconnect() = 0;

        virtual bool write1Byte(uint8_t id, uint16_t address, uint8_t value) = 0;

        virtual bool write2Byte(uint8_t id, uint16_t address, uint16_t value) = 0;

        virtual bool read1Byte(uint8_t id, uint16_t address, uint8_t *data) = 0;

        virtual bool read2Byte(uint8_t id, uint16_t address, uint16_t *data) = 0;
    };
}
#endif //COMSBASE_H
