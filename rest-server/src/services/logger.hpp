// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#ifndef LOGGER_H
#define LOGGER_H
#include <spdlog/spdlog.h>
#include <string>
#include <vector>
#include "logger_interface.hpp"

namespace cadg_rest {
class Logger : public LoggerInterface {
  public:
    static Logger& Instance();
    Logger(Logger const&) = delete;
    void operator=(Logger const&) = delete;
    std::string StringifyCollection(std::string name, std::map<std::string, std::string> map);

    void Log(int log_level, std::string message) override;
    void Log(int log_level, std::string message, std::string calling_class,
                    std::string calling_method) override;
    void Log(int log_level, std::string message, std::string calling_class,
                    std::string calling_method, std::vector<std::string> args) override;
    void LogNetworkActivity(http_request message, std::string endpoint, int verbosity = 0) override;
    void LogLevel(int log_level) override;
  protected:
    spdlog::level::level_enum ConvertLogLevel(int log_level);
  private:
    Logger();
    int log_level__;
    std::unique_ptr<spdlog::logger> p_logger__;
    std::unique_ptr<spdlog::logger> p_net_logger__;
};
}
#endif // LOGGER_H
