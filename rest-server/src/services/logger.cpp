// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#include <iostream>
#include <map>
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
    if (log_level__ <= log_level)
        p_logger__->log(ConvertLogLevel(log_level), message);
}
void Logger::Log(int log_level, std::string message, std::string calling_class,
            std::string calling_method) {
    if (log_level__ <= log_level) {
        std::string message_constructor("");
        message_constructor.append("Class: " + calling_class);
        message_constructor.append(" Method: " + calling_method);
        message_constructor.append(" Message: " + message);
        Log(log_level, message_constructor);
    }
}
void Logger::Log(int log_level, std::string message, std::string calling_class,
            std::string calling_method, std::vector<std::string> args) {
    if (log_level__ <= log_level) {
        std::string message_constructor("");
        message_constructor.append("Class: " + calling_class);
        message_constructor.append(" Method: " + calling_method);
        message_constructor.append(" Message: " + message);
        message_constructor.append(" Args: ");
        for (const auto& arg : args)
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
    if (verbosity > 0) {
        std::map<std::string, std::string> headers_map;
        for (auto const& header : message.headers())
            headers_map[header.first] = header.second;
        log.append(StringifyCollection("headers", headers_map));
    }
    std::cout << log << std::endl;
}
void Logger::LogLevel(int log_level) {
    /* to set the internal log level */
    log_level__ = log_level;

    /* alternatively, to only adjust the logging at the spdlog console level */
    // p_logger__->sinks()[0]->set_level(ConvertLogLevel(log_level));

    /* alternatively, to set all spdlog logging sinks to the same level below */
    // for(auto& sink : ) 
    //     sink->set_level(ConvertLogLevel(log_level));
}
spdlog::level::level_enum Logger::ConvertLogLevel(int log_level) {
    switch (log_level) {
        case 0: return spdlog::level::trace;
        case 1: return spdlog::level::debug;
        case 2: return spdlog::level::info;
        case 3: return spdlog::level::warn;
        case 4: return spdlog::level::err;
        case 5: return spdlog::level::critical;
        default: return spdlog::level::off;
    }
}
Logger::Logger() {
    auto console_sink = std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>();
    console_sink->set_level(spdlog::level::trace);  // trace level will log everything

    auto file_sink = std::make_shared<spdlog::sinks::simple_file_sink_mt>("logs/logs.txt", true);
    file_sink->set_level(spdlog::level::trace);  // trace level will log everything

    p_logger__.reset(new spdlog::logger("multi_sink", {console_sink, file_sink}));
    p_logger__->set_level(spdlog::level::trace);  // trace level will log everything
    p_logger__->flush_on(spdlog::level::trace);  // trace level will flush to file on every log message
    p_logger__->warn("this should appear in both console and file");
    p_logger__->info("this message should not appear in the console, only in the file");
}
}  // namespace cadg_rest
