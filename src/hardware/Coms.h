//
// Created by ceyx on 12/17/24.
//

#ifndef COMS_H
#define COMS_H

#include <cmath>
#include <string>

#include "ComsBase.h"

#include "dynamixel_sdk/dynamixel_sdk.h"

namespace hardware {
    class Coms final : public ComsBase {
    public:
        Coms(const std::string &port_name, int baud_rate);

        ~Coms() override;

        bool connect() override;

        void disconnect() override;

        bool write1Byte(uint8_t id, uint16_t address, uint8_t value) override;

        bool write2Byte(uint8_t id, uint16_t address, uint16_t value) override;

        bool read1Byte(uint8_t id, uint16_t address, uint8_t *data) override;

        bool read2Byte(uint8_t id, uint16_t address, uint16_t *data) override;

    protected:
        dynamixel::PortHandler *port_handler_;
        dynamixel::PacketHandler *packet_handler_;
        int baud_rate_;

        uint8_t dxl_error_ = 0;
        const double_t PROTOCOL_VERSION = 1.0;
    };
}


#endif //COMS_H
