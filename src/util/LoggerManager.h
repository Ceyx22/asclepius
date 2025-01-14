//
// Created by ceyx on 12/29/24.
//

#ifndef LOGGERMANAGER_H
#define LOGGERMANAGER_H

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <memory>

namespace util {
    class LoggerManager {
    public:
        static std::shared_ptr<spdlog::logger> getLogger();

    private:
        LoggerManager();

        static void initialize();

        static std::shared_ptr<spdlog::logger> logger;
    };
} // util

#endif //LOGGERMANAGER_H
