///Mocks the CADG Logger for testing purposes
/**
 * (License)
 * @file    mock_logger.hpp
 * @authors { Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley, Shawn Hulce, Michael McCulley }
 * @date    1/9/2019
 */

#ifndef CADG_MOCK_LOGGER_HPP
#define CADG_MOCK_LOGGER_HPP
#include "logger_interface.hpp"
#include <spdlog/spdlog.h>
#include <map>
#include <string>
#include <vector>

namespace cadg_rest {
class MockLogger : public LoggerInterface {
  public:
      MockLogger(){};
      MockLogger(MockLogger const &) = delete;
      void operator=(MockLogger const &) = delete;
      std::string StringifyCollection(std::string name, std::map <std::string, std::string> map){
        std::string json_string;
        json_string.append("Stringified Collection");
        return json_string;
      };
      void Log(int log_level, std::string message) override { };
      void Log(int log_level, std::string message, std::string calling_class,
               std::string calling_method) override { };
      void Log(int log_level, std::string message, std::string calling_class,
               std::string calling_method, std::vector <std::string> args) override { };
      void LogNetworkActivity(http_request message, std::string endpoint, int verbosity = 0) override { };
      void LogLevel(int log_level) override { };

  protected:
      spdlog::level::level_enum ConvertLogLevel(int log_level){ return spdlog::level::off; };

  private:
      int log_level__;
      std::unique_ptr <spdlog::logger> p_logger__;
      std::unique_ptr <spdlog::logger> p_net_logger__;
};
}

#endif //CADG_MOCK_LOGGER_HPP
