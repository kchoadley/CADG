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
    std::string name;
    int id;
    std::string type;
    std::string format;
    std::string ip;
    /**
     * Converts the disseminator entity to a json object.
     * 
     * @return a json object representation of a disseminator.
     * 
     */
    web::json::value to_json() {
        auto d_json  = web::json::value::object();
        d_json["id"] = web::json::value::string(std::to_string(id));
        d_json["name"] = web::json::value::string(name);
        d_json["type"] = web::json::value::string(type);
        d_json["format"] = web::json::value::string(format);
        d_json["ip"] = web::json::value::string(ip);
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
            if(     d_json.has_field("id") && d_json["id"].is_integer()
                    && d_json.has_field("name") && d_json["name"].is_string()
                    && d_json.has_field("type") && d_json["type"].is_string()
                    && d_json.has_field("format") && d_json["format"].is_string()
                    && d_json.has_field("ip") && d_json["ip"].is_string()) {
                Disseminator disseminator;
                disseminator.id = d_json["id"].as_integer();
                disseminator.name = d_json["name"].as_string();
                disseminator.type = d_json["type"].as_string();
                disseminator.format = d_json["format"].as_string();
                disseminator.ip = d_json["ip"].as_string();
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
        && a.ip == b.ip;
}
}
#endif // DISSEMINATOR_H