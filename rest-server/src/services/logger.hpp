// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
#include <string>
#include <vector>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "logger_interface.hpp"

namespace cadg_rest {
class Logger : public LoggerInterface {
  public:
    static Logger& Instance();
    Logger(Logger const&) = delete;
    void operator=(Logger const&) = delete;

    void Log(LogLevel log_level, std::string message) override;
    void Log(LogLevel log_level, std::string message, std::string calling_class,
                    std::string calling_method) override;
    void Log(LogLevel log_level, std::string message, std::string calling_class,
                    std::string calling_method, std::vector<std::string> args) override;
    void LogNetworkActivity(http_request message) override;
    void LogLevel(LogLevel log_level) override;
  private:
    Logger() {
        try
        {
            auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            console_sink->set_level(spdlog::level::warn);
            console_sink->set_pattern("[multi_sink_example] [%^%l%$] %v");

            auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/multisink.txt", true);
            file_sink->set_level(spdlog::level::trace);

            spd_logger__("multi_sink", {console_sink, file_sink});
            spd_logger__.set_level(spdlog::level::debug);
            spd_logger__.warn("this should appear in both console and file");
            spd_logger__.info("this message should not appear in the console, only in the file");
        }
        catch (const spdlog::spdlog_ex& ex)
        {
            std::cout << "Log initialization failed: " << ex.what() << std::endl;
        }
        logger();
    }
    spdlog::logger spd_logger__;
};
}
#endif // LOGGER_H
