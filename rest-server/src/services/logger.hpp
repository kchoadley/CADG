// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/// A logger.
/**
 * This logger adhers to the LoggerInterface. It is a singleton,
 * accessed through the static method Instance().
 *
 * @file        logger.hpp
 * @authors     Kristofer Hoadley
 * @date        November, 2018
 */
#ifndef LOGGER_H
#define LOGGER_H
#include <spdlog/spdlog.h>
#include <string>
#include <vector>
#include "logger_interface.hpp"

namespace cadg_rest {
/// A logger.
/**
 * Logger implements application logging and network logging. 
 */
class Logger : public LoggerInterface {
  public:
    /// Instance returns a reference to the Logger.
    /**
     * Instance implements the Singleton design pattern.
     */
    static Logger& Instance();
    /// Deletes the copy constructor to enforce singleton.
    Logger(Logger const&) = delete;
    /// Deletes the assignment constructor to enforce singleton.
    void operator=(Logger const&) = delete;
    /**
     * Converts a map collection of string to string into a single string in a json valid format.
     * 
     * @param name The name of the collection.
     * @param map Map representation of the collection.
     * @return A string representation of the collection.
     */
    std::string StringifyCollection(std::string name, std::map<std::string, std::string> map);

    void Log(int log_level, std::string message) override;
    void Log(int log_level, std::string message, std::string calling_class,
                    std::string calling_method) override;
    void Log(int log_level, std::string message, std::string calling_class,
                    std::string calling_method, std::vector<std::string> args) override;
    void LogNetworkActivity(http_request message, std::string endpoint, int verbosity = 0) override;
    void LogLevel(int log_level) override;
  protected:
    /**
     * Converts an integer log level, as defined in log_level.hpp, to
     * the level_enum of spdlog.
     * 
     * @param log_level Integer representation of the log level to convert.
     * @return The equivelant log level enum of spdlog.
     */
    spdlog::level::level_enum ConvertLogLevel(int log_level);
  private:
    Logger();
    int log_level__;
    std::unique_ptr<spdlog::logger> p_logger__;
    std::unique_ptr<spdlog::logger> p_net_logger__;
};
}
#endif // LOGGER_H
