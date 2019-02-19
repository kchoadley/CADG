// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/**
 * A struct representing the Alert Disseminator entity.
 *
 * @file        disemminator.hpp
 * @authors     Michael McCulley
 * @date        January, 2019
 */
#ifndef DISSEMINATOR_H
#define DISSEMINATOR_H
#include <string>
#include <vector>
#include <cpprest/json.h>
#include "logger_interface.hpp"

namespace cadg_rest {
struct Disseminator {
    int id;
    std::string name;
    std::string type;
    std::string format;
    std::string ip;
    int port;
    int backup_port;
    std::string status;
    /**
     * Converts the disseminator entity to a json object.
     * 
     * @return a json object representation of a disseminator.
     * 
     */
    web::json::value to_json() {
        auto d_json  = web::json::value::object();
        d_json["id"] = web::json::value::number(id);
        d_json["name"] = web::json::value::string(name);
        d_json["type"] = web::json::value::string(type);
        d_json["format"] = web::json::value::string(format);
        d_json["ip"] = web::json::value::string(ip);
        d_json["port"] = web::json::value::number(port);
        d_json["backup_port"] = web::json::value::number(backup_port);
        d_json["status"] = web::json::value::string(status);
        return d_json;
    }
    /**
     * Creates an optional<Disseminator> from a web::json::value.
     * 
     * If the json value does not contain all required fields,
     * a std::nullopt is returned.
     * 
     * @return std::optional<Disseminator>
     */     
    static std::optional<Disseminator> from_json(web::json::value d_json) {
        try {
            if(     d_json.has_field("name") && d_json["name"].is_string() &&
                    d_json.has_field("type") && d_json["type"].is_string() &&
                    d_json.has_field("format") && d_json["format"].is_string() &&
                    d_json.has_field("ip") && d_json["ip"].is_string() &&
                    d_json.has_field("port") && d_json["port"].is_integer() &&
                    d_json.has_field("backup_port") && d_json["backup_port"].is_integer() &&
                    d_json.has_field("status") && d_json["status"].is_string()) {
                Disseminator disseminator;
                if (d_json.has_field("id")) {
                    if (d_json["id"].is_integer())
                        disseminator.id = d_json["id"].as_integer();
                    else  // wrong type for valid field
                        return std::nullopt;
                }
                disseminator.name = d_json["name"].as_string();
                disseminator.type = d_json["type"].as_string();
                disseminator.format = d_json["format"].as_string();
                disseminator.ip = d_json["ip"].as_string();
                disseminator.port = d_json["port"].as_integer();
                disseminator.backup_port = d_json["backup_port"].as_integer();
                disseminator.status = d_json["status"].as_string();
                return disseminator;
            } else {
                return std::nullopt;
            }
        } catch (std::exception&  e) {
            return std::nullopt;
        }
    }      
};
/// Necessary for comparing if two disseminators are equal.
inline bool operator==(const Disseminator &a, const Disseminator &b) {
    return a.id == b.id 
        && a.name == b.name
        && a.type == b.type
        && a.format == b.format
        && a.ip == b.ip
        && a.port == b.port
        && a.backup_port == b.backup_port
        && a.status == b.status;
}
}
#endif // DISSEMINATOR_H