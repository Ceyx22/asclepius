//
// Coms object to prevent multiple instance of the single coms parameter
// Created by ceyx on 12/17/24.
//
#define FMT_HEADER_ONLY
#include "Coms.h"
#include "util/LoggerManager.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"


#define PROTOCOL_VERSION 1.0

namespace hardware {
    Coms::Coms(const std::string &port_name, const int baud_rate) {
        baud_rate_ = baud_rate;
        port_handler_ = dynamixel::PortHandler::getPortHandler(port_name.c_str());
        packet_handler_ = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);
    }

    /*
     * Goes through and establishes a connection to the port and
     * sets the baud rate
     */
    void Coms::connect() const {
        if (port_handler_->openPort() == false) {
            spdlog::error("Failed to open port");
            // throw exception
        }
        spdlog::info("Port opened ");

        if (port_handler_->setBaudRate(baud_rate_) == false) {
            spdlog::error("Failed to set baud rate");
            //throw exception
        }
        spdlog::info("Set baud rate ");
    }


    /*
     * Writes the 2 bytes to the motor
     */
    bool Coms::write2ByteTxRx(const uint8_t dynamixel_id, const uint16_t address, const uint16_t value) {
        if (packet_handler_->write2ByteTxRx(port_handler_, dynamixel_id, address, value, &dxl_error_) != COMM_SUCCESS) {
            spdlog::error("Failed to write from port, Error msg: {}", dxl_error_);
            return false;
        }
        return true;
    };

    /*
     * Writes the byte to the motor
     */
    bool Coms::write1ByteTxRx(const uint8_t dynamixel_id, const uint16_t address, const uint8_t value) {
        if (packet_handler_->write1ByteTxRx(port_handler_, dynamixel_id, address, value, &dxl_error_) != COMM_SUCCESS) {
            spdlog::error("Failed to write from port, Error msg: {}", dxl_error_);
            return false;
        }
        return true;
    };

    /*
     * Reads the 2 bytes to the motor
     */
    bool Coms::read2ByteTxRx(const uint8_t dynamixel_id, const uint16_t address, uint16_t *data) {
        if (packet_handler_->read2ByteTxRx(port_handler_, dynamixel_id, address, data, &dxl_error_) != COMM_SUCCESS) {
            spdlog::error("Failed to read from port, Error msg: {}", dxl_error_);
            return false;
        }
        return true;
    };

    /*
     * Reads the byte to the motor
     */
    bool Coms::read1ByteTxRx(const uint8_t dynamixel_id, const uint16_t address, uint8_t *data) {
        if (packet_handler_->read1ByteTxRx(port_handler_, dynamixel_id, address, data, &dxl_error_) != COMM_SUCCESS) {
            spdlog::error("Failed to read from port, Error msg: {}", dxl_error_);
            return false;
        }

        return true;
    };

    /*
     * Closes the port
     * deletes the port_handler
     * deletes the packet_handler
     */
    void Coms::disconnect() const {
        util::LoggerManager::getLogger()->info("Disconnecting");
        port_handler_->closePort();

        delete port_handler_;
        delete packet_handler_;
    }
}
