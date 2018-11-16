// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
#include <string>
#include <vector>
#include "logger_interface.hpp"
#include "log_level.hpp"

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
    Logger() { }
    //LogLevel level = LogLevel::WARN;  // default log level
};
}
#endif // LOGGER_H
