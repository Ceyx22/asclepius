//
// Coms object to prevent multiple instance of the single coms parameter
// Created by ceyx on 12/17/24.
//
#define FMT_HEADER_ONLY
#include "Coms.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"


#define PROTOCOL_VERSION 1.0

namespace hardware {
    Coms::Coms(const std::string &port_name, const int baud_rate) {
        baud_rate_ = baud_rate;
        port_handler_ = dynamixel::PortHandler::getPortHandler(port_name.c_str());
        packet_handler_ = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);
    }


    bool Coms::connect() {
        // Open Serial Port
        dxl_com_result_ = port_handler_->openPort();
        if (dxl_com_result_ == false) {
            spdlog::error("Failed to open port");
            return false;
        }
        spdlog::info("Port opened ");

        // Set the baud rate of the serial port (use DYNAMIXEL Baud rate)
        dxl_com_result_ = port_handler_->setBaudRate(baud_rate_);
        if (dxl_com_result_ == false) {
            spdlog::error("Failed to set baud rate");
            return false;
        }
        spdlog::info("Set baud rate ");

        return true;
    }

    bool Coms::write2ByteTxRx(const uint8_t dynamixel_id, uint16_t address, uint16_t value) {
        dxl_com_result_ = packet_handler_->write2ByteTxRx(port_handler_, dynamixel_id, address, value, &dxl_error_);

        if (dxl_com_result_ != COMM_SUCCESS) {
            spdlog::error("Failed to write from port");
            return false;
        }
        return true;
    };

    bool Coms::write1ByteTxRx(const uint8_t dynamixel_id, const uint16_t address, const uint8_t value) {
        dxl_com_result_ = packet_handler_->write1ByteTxRx(port_handler_, dynamixel_id, address, value, &dxl_error_);

        if (dxl_com_result_ != COMM_SUCCESS) {
            spdlog::error("Failed to write from port");
            return false;
        }
        return true;
    };

    bool Coms::read2ByteTxRx(const uint8_t dynamixel_id, const uint16_t address, uint16_t *data) {
        dxl_com_result_ = packet_handler_->read2ByteTxRx(port_handler_, dynamixel_id, address, data, &dxl_error_);

        if (dxl_com_result_ != COMM_SUCCESS) {
            spdlog::error("Failed to read from port");
            return false;
        }
        return true;
    };

    bool Coms::read1ByteTxRx(const uint8_t dynamixel_id, const uint16_t address, uint8_t *data) {
        dxl_com_result_ = packet_handler_->read1ByteTxRx(port_handler_, dynamixel_id, address, data, &dxl_error_);

        if (dxl_com_result_ != COMM_SUCCESS) {
            spdlog::error("Failed to read from port");
            return false;
        }

        return true;
    };

    void Coms::disconnect() const {
        spdlog::info("Disconnecting...");
        port_handler_->closePort();

        delete packet_handler_;
        delete port_handler_;
    }
}
