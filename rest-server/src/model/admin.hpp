// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/**
 * Contains an admin data struct for moving admin data to/from
 * a data store and a REST endpoint.
 *
 * @file        admin.hpp
 * @authors     Kristofer Hoadley
 * @date        January, 2019
 */
#ifndef ADMIN_H
#define ADMIN_H
#include <string>
#include <cpprest/json.h>

namespace cadg_rest {
/**
 * An admin struct which contains a name, id, and email.
 */
struct Admin {
    std::string name;
    int id;
    std::string email;
    /**
     * Converts the admin struct to a json object.
     * 
     * The id of the admin is to be set to the object name.
     * 
     * @return a json object representation of a admin.
     * 
     */
    web::json::value to_json() {
        auto admin_json  = web::json::value::object();
        admin_json["name"] = web::json::value::string(name);
        admin_json["email"] = web::json::value::string(email);
        return admin_json;
    }
};
/// Necessary for comparing if two admins are equal.
inline bool operator==(const Admin &a, const Admin &b) {
    return a.name == b.name &&
           a.id == b.id &&
           a.email == b.email;
}
}
#endif // ADMIN_H
