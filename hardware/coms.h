//
// Created by ceyx on 12/17/24.
//

#ifndef COMS_H
#define COMS_H

#include <string>

#include "dynamixel_sdk/dynamixel_sdk.h"
#define PROTOCOL_VERSION 1.0

namespace hardware {
    class coms {
    protected:
        dynamixel::PortHandler *port_handler_;
        dynamixel::PacketHandler *packet_handler_;
        int baud_rate_;

        uint8_t dxl_error_ = 0;
        uint8_t dxl_com_result_ = 0;

    public:
        coms(const std::string &port_name, int baud_rate);

        bool connect();

        void disconnect() const;

        bool write2ByteTxRx(uint8_t dynamixel_id, uint16_t address, uint16_t value);

        bool write1ByteTxRx(uint8_t dynamixel_id, uint16_t address, uint8_t value);

        bool read2ByteTxRx(uint8_t dynamixel_id, uint16_t address, uint16_t *data);

        bool read1ByteTxRx(uint8_t dynamixel_id, uint16_t address, uint8_t *data);
    };
}


#endif //COMS_H
