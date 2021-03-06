/// General implementation of Controller.
/**
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
                    Shawn Hulce, Michael McCulley

 * @file        controller.cpp
 * @authors     Kristofer Hoadley
 * @date        November, 2018
 */
#include <pplx/pplxtasks.h>
#include <controller.hpp>
#include <map>
#include <string>
#include <vector>
#include "network_utils.hpp"

namespace cadg_rest {
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
std::vector<std::string> Controller::PathSegments(const std::string& path_string) {
    std::vector<std::string> parsed_path;
    std::string token_delimeter = "/";
    for (int begining_position = 0, ending_position = 0;
                ending_position < path_string.length() && begining_position < path_string.length();
                begining_position = ending_position + token_delimeter.length()) {
        ending_position = path_string.find(token_delimeter, begining_position);
        if (ending_position == std::string::npos)  // found the end of the query string
            ending_position = path_string.length();
        std::string token = path_string.substr(begining_position, ending_position - begining_position);
        if (!token.empty())
            parsed_path.push_back(token);
    }
    return parsed_path;
}
/// Extracts individual queries from a query string.
/**
 * Some limitations of this implementation:
 * Does not handle converting spaces (%20) or other special characters.
 * Does not handle delimiting queries by ';'
 * Does not handle multiple values for a key (keeps the last one).
 * @param   query_string    full query string to extract queries from
 * @return  map of individual queries using the query key as the map key
 */
std::map<std::string, std::string> Controller::Queries(const std::string& query_string) {
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
