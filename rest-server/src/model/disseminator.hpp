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
#include <cpprest/json.h>

namespace cadg_rest {
struct Disseminator {
    std::string name;
    int id;
    std::string type;
    std::string format;
    /**
     * Converts the disseminator entity to a json object.
     * 
     * @return a json object representation of a admin.
     * 
     */
    web::json::value to_json() {
        auto d_json  = web::json::value::object();
        d_json["id"] = web::json::value::string(id);
        d_json["name"] = web::json::value::string(name);
        d_json["type"] = web::json::value::string(type);
        d_json["format"] = web::json::value::string(format);
        return d_json;
    }
};
/// Necessary for comparing if two admins are equal.
inline bool operator==(const Disseminator &a, const Disseminator &b) {
    return a.id == b.id &&
           a.name == b.name &&
           a.type == b.type &&
           a.format == b.format;
}
}
#endif // DISSEMINATOR_H