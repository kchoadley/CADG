// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#include <pplx/pplxtasks.h>
#include <controller.hpp>
#include <map>
#include <string>
#include <vector>
#include "network_utils.hpp"

namespace cadg_rest {
Controller::Controller() {}
Controller::~Controller() {}
void Controller::endpoint(const std::string& value) {
    uri endpointURI(value);
    uri_builder endpointBuilder;
    endpointBuilder.set_scheme(endpointURI.scheme());
    if (endpointURI.host() == "host_auto_ip4")
        endpointBuilder.set_host(NetworkUtils::hostIP4());
    else if (endpointURI.host() == "host_auto_ip6")
        endpointBuilder.set_host(NetworkUtils::hostIP6());
    endpointBuilder.set_port(endpointURI.port());
    endpointBuilder.set_path(endpointURI.path());
    listener__ = http_listener(endpointBuilder.to_uri());
}
std::string Controller::endpoint() const {
    return listener__.uri().to_string();
}
pplx::task<void> Controller::Accept() {
    InitHandlers();
    return listener__.open();
}
pplx::task<void> Controller::Shutdown() {
    return listener__.close();
}
/**
 * Generate a string that can be used for logging the http request.
 * 
 * The verbosity is optional, with lowest verbosity the default.
 * 0 is low verbosity, 1 is medium verbosity, 2 is high verbosity.
 * 
 */
std::string Controller::LogString(const http_request& message, int verbosity) {
    std::string log;
    log.append(message.method() + " ");
    log.append(endpoint());
    log.append(message.relative_uri().to_string() + " ");
    if (verbosity > 0) {
        std::map<std::string, std::string> headers_map;
        for (auto const& header : message.headers())
            headers_map[header.first] = header.second;
        log.append(StringifyCollection("headers", headers_map));
    }
    if (verbosity > 1) {
        log.append(StringifyCollection("queries", Queries(message.relative_uri().query())));
    }
    return log;
}
std::string Controller::StringifyCollection(std::string name, std::map<std::string, std::string> map) {
    std::string json_string;
    json_string.append("\"" + name +"\": [");
    for (auto const& item : map)
        json_string.append("\"" + item.first + "\": \"" + item.second + "\", ");
    json_string = json_string.substr(0, json_string.size()-2);
    json_string.append("] ");
    return json_string;
}
std::map<std::string, std::string> Controller::Queries(std::string query_string) {
    std::map<std::string, std::string> query_map;
    std::string query_delimeter = "&";  // technically, it could be delimited by ';' too
    std::string value_delimeter = "=";
    for (int begining_position = 0, ending_position = 0;
                ending_position < query_string.length() && begining_position < query_string.length();
                begining_position = ending_position + query_delimeter.length()) {
        ending_position = query_string.find(query_delimeter, begining_position);
        if (ending_position == std::string::npos)  // found the end of the query string
            ending_position = query_string.length();
        std::string token = query_string.substr(begining_position, ending_position - begining_position);
        if (!token.empty()) {
            int name_value_split = token.find(value_delimeter, 0);
            if (name_value_split != std::string::npos) {
                std::string name = token.substr(0, name_value_split);
                std::string value = token.substr(name_value_split + value_delimeter.length());
                query_map[name] = value;
            }
        }
    }
    return query_map;
}
json::value Controller::ResponseNotImpl(const http::method & method) {
    auto response = json::value::object();
    response["http_method"] = json::value::string(method);
    response["serviceName"] = json::value::string("CADG Service");
    return response;
}
}  // namespace cadg_rest
