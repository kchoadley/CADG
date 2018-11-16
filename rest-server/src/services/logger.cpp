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
void Logger::LogNetworkActivity(http_request message, int verbosity = 0) {
    std::string log;
    log.append(message.method() + " ");
    log.append(endpoint());
    log.append(message.relative_uri().to_string() + " ");
    if(verbosity > 0) {
        std::map<std::string, std::string> headers_map;
        for (auto const& header : message.headers())
            headers_map[header.first] = header.second;
        log.append(StringifyCollection("headers", headers_map));
    }
    if(verbosity > 1) {
        log.append(StringifyCollection("queries", Queries(message.relative_uri().query())));
    }
    std::cout << log << std::endl;
}
void Logger::LogLevel(LogLevel log_level) {
    //level = log_level;
}
}  // namespace cadg_rest
