// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#include <iostream>
#include <string>
#include <vector>
#include "logger.hpp"

namespace cadg_rest {
Logger& Logger::Instance() {
    static Logger instance;
    return instance;
}
std::string Logger::StringifyCollection(std::string name, std::map<std::string, std::string> map) {
    std::string json_string;
    json_string.append("\"" + name +"\": [");
    for (auto const& item : map)
        json_string.append("\"" + item.first + "\": \"" + item.second + "\", ");
    json_string = json_string.substr(0, json_string.size()-2);
    json_string.append("] ");
    return json_string;
}

void Logger::Log(int log_level, std::string message) {
    if(log_level__ <= log_level) {
        std::cout << message << std::endl;
    }
}
void Logger::Log(int log_level, std::string message, std::string calling_class,
            std::string calling_method) {
    if(log_level__ <= log_level) {
        std::string message_constructor("");
        message_constructor.append("Class: " + calling_class);
        message_constructor.append(" Method: " + calling_method);
        message_constructor.append(" Message: " + message);
        Log(log_level, message_constructor);
    }
}
void Logger::Log(int log_level, std::string message, std::string calling_class,
            std::string calling_method, std::vector<std::string> args) {
    if(log_level__ <= log_level) {
        std::string message_constructor("");
        message_constructor.append("Class: " + calling_class);
        message_constructor.append(" Method: " + calling_method);
        message_constructor.append(" Message: " + message);
        message_constructor.append(" Args: ");
        for(const auto& arg: args) 
            message_constructor.append(arg + ", ");
        message_constructor = message_constructor.substr(0, message_constructor.size()-2);
        Log(log_level, message_constructor);
    }
}
void Logger::LogNetworkActivity(http_request message, std::string endpoint, int verbosity) {
    std::string log;
    log.append(message.method() + " ");
    log.append(endpoint);
    log.append(message.relative_uri().to_string() + " ");
    if(verbosity > 0) {
        std::map<std::string, std::string> headers_map;
        for (auto const& header : message.headers())
            headers_map[header.first] = header.second;
        log.append(StringifyCollection("headers", headers_map));
    }
    std::cout << log << std::endl;
}
void Logger::LogLevel(int log_level) {
    log_level__ = log_level;
}
}  // namespace cadg_rest
