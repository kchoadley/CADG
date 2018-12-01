//
// Created by Vaniya on 11/30/2018.
//

#ifndef CADG_MOCK_LOGGER_INTERFACE_HPP
#define CADG_MOCK_LOGGER_INTERFACE_HPP
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <cpprest/http_msg.h>
#include <cpprest/http_listener.h>
#include "logger_interface.hpp"
using namespace std;
using namespace web;
using namespace http;

namespace cadg_rest{
class MockLogger : public LoggerInterface {
public:
    MOCK_METHOD2(Log, void(int log_level, std::string message));
    MOCK_METHOD4(Log, void(int log_level, std::string message, std::string calling_class,
            std::string calling_method));
    MOCK_METHOD5(Log, void(int log_level, std::string message, std::string calling_class,
            std::string calling_method, std::vector<std::string> args));
    MOCK_METHOD3(LogNetworkActivity, void(http_request message, std::string endpoint, int verbosity));
    MOCK_METHOD1(LogLevel, void(int log_level));
};
}
#endif //CADG_MOCK_LOGGER_INTERFACE_HPP
