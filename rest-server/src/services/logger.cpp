// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
#include <string>
#include <vector>
#include <spdlog/spdlog>
#include <spdlog/sinks/stdout_color_sinks>
#include <spdlog/sinks/basic_file_sink>
#include "logger_interface.hpp"

namespace cadg_rest {
static Logger::Logger& Instance();

void Logger::Log(LogLevel log_level, std::string message) {
    // TO-DO: Implementation
}
void Logger::Log(LogLevel log_level, std::string message, std::string calling_class,
        std::string calling_method) {
    // TO-DO: Implementation
    }
void Logger::Log(LogLevel log_level, std::string message, std::string calling_class,
        std::string calling_method, std::vector<std::string> args) {
    // TO-DO: Implementation
    }
void Logger::LogNetworkActivity(http_request message) {
    // TO-DO: Implementation
}
void Logger::LogLevel(LogLevel log_level) {
    // TO-DO: Implementation
}
}
#endif // LOGGER_H
