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
    int user_id;
    std::string first_name;
    std::string last_name;
    std::string username;
    std::string password;
    std::string email;
    std::string phone;
    std::string address;
    std::string country;
    std::string state_region;
    std::string zip;
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
        admin_json["user_id"] = web::json::value::number(user_id);
        admin_json["first_name"] = web::json::value::string(first_name);
        admin_json["last_name"] = web::json::value::string(last_name);
        admin_json["username"] = web::json::value::string(username);
        admin_json["password"] = web::json::value::string(password);
        admin_json["email"] = web::json::value::string(email);
        admin_json["phone"] = web::json::value::string(phone);
        admin_json["address"] = web::json::value::string(address);
        admin_json["country"] = web::json::value::string(country);
        admin_json["state_region"] = web::json::value::string(state_region);
        admin_json["zip"] = web::json::value::string(zip);
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
