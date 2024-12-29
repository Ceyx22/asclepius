//
// Coms object to prevent multiple instance of the single coms parameter
// Created by ceyx on 12/17/24.
//

#include "coms.h"

#include <iostream>

#define PROTOCOL_VERSION 1.0

namespace hardware {
    coms::coms(const std::string &port_name, const int baud_rate) {
        baud_rate_ = baud_rate;
        port_handler_ = dynamixel::PortHandler::getPortHandler(port_name.c_str());
        packet_handler_ = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);
    }


    bool coms::connect() {
        // Open Serial Port
        dxl_com_result_ = port_handler_->openPort();
        if (dxl_com_result_ == false) {
            std::cout << "Failed to open port" << std::endl;
            return false;
        }
        std::cout << "Port opened" << std::endl;

        // Set the baud rate of the serial port (use DYNAMIXEL Baud rate)
        dxl_com_result_ = port_handler_->setBaudRate(baud_rate_);
        if (dxl_com_result_ == false) {
            std::cout << "Failed to set baud rate" << std::endl;
            return false;
        }
        std::cout << "Set baud rate" << std::endl;

        return true;
    }

    bool coms::write2ByteTxRx(const uint8_t dynamixel_id, uint16_t address, uint16_t value) {
        dxl_com_result_ = packet_handler_->write2ByteTxRx(port_handler_, dynamixel_id, address, value, &dxl_error_);

        if (dxl_com_result_ != COMM_SUCCESS) {
            std::cout << "Failed to write to port" << std::endl;
            return false;
        }
        return true;
    };

    bool coms::write1ByteTxRx(const uint8_t dynamixel_id, const uint16_t address, const uint8_t value) {
        dxl_com_result_ = packet_handler_->write1ByteTxRx(port_handler_, dynamixel_id, address, value, &dxl_error_);

        if (dxl_com_result_ != COMM_SUCCESS) {
            std::cout << "Failed to write to port" << std::endl;
            return false;
        }
        return true;
    };

    bool coms::read2ByteTxRx(const uint8_t dynamixel_id, const uint16_t address, uint16_t *data) {
        dxl_com_result_ = packet_handler_->read2ByteTxRx(port_handler_, dynamixel_id, address, data, &dxl_error_);

        if (dxl_com_result_ != COMM_SUCCESS) {
            std::cout << "Failed to read from port" << std::endl;
            return false;
        }
        return true;
    };

    bool coms::read1ByteTxRx(const uint8_t dynamixel_id, const uint16_t address, uint8_t *data) {
        dxl_com_result_ = packet_handler_->read1ByteTxRx(port_handler_, dynamixel_id, address, data, &dxl_error_);

        if (dxl_com_result_ != COMM_SUCCESS) {
            std::cout << "Failed to read from port" << std::endl;
            return false;
        }

        return true;
    };

    void coms::disconnect() const {
        std::cout << "Port closing" << std::endl;
        port_handler_->closePort();

        delete packet_handler_;
        delete port_handler_;
    }
}
