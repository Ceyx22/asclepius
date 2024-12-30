//
// Created by ceyx on 12/29/24.
//
#define FMT_HEADER_ONLY
#include "LoggerManager.h"
// #include <spdlog/spdlog.h>
// #include <spdlog/sinks/basic_file_sink.h>


namespace util {
    std::shared_ptr<spdlog::logger> LoggerManager::logger = nullptr;

    LoggerManager::LoggerManager() {
        // Private constructor (no instantiation allowed)
    }

    void LoggerManager::initialize() {
        if (!logger) {
            auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            console_sink->set_level(spdlog::level::info);

            auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/application.log", true);
            file_sink->set_level(spdlog::level::debug);

            logger = std::make_shared<spdlog::logger>("multi_sink", spdlog::sinks_init_list{console_sink, file_sink});
            logger->set_level(spdlog::level::debug);
            spdlog::set_default_logger(logger);
            spdlog::flush_on(spdlog::level::info); // Flush logs on info or higher
        }
    }

    std::shared_ptr<spdlog::logger> LoggerManager::getLogger() {
        if (!logger) {
            initialize();
        }
        return logger;
    }
} // util
