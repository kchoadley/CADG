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
#include <optional>
#include <string>
#include <cpprest/json.h>

namespace cadg_rest {
/**
 * An admin struct which contains a name, id, and email.
 */
struct Admin {
    int id;
    std::string first_name;
    std::string last_name;
    std::string username;
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
        admin_json["id"] = web::json::value::number(id);
        admin_json["first_name"] = web::json::value::string(first_name);
        admin_json["last_name"] = web::json::value::string(last_name);
        admin_json["username"] = web::json::value::string(username);
        admin_json["email"] = web::json::value::string(email);
        admin_json["phone"] = web::json::value::string(phone);
        admin_json["address"] = web::json::value::string(address);
        admin_json["country"] = web::json::value::string(country);
        admin_json["state_region"] = web::json::value::string(state_region);
        admin_json["zip"] = web::json::value::string(zip);
        return admin_json;
    }
    /**
     * Creates an Admin from a web::json::value
     * 
     * If the web::json::value does not have all the needed fields with the correct types
     * will return a std::nullopt
     * 
     * @return an Admin
     * 
     */
    std::optional<Admin> from_json(web::json::value admin_json) {
        if (    admin_json.has_field("id")              && admin_json["id"].is_integer() &&
                admin_json.has_field("first_name")      && admin_json["first_name"].is_string() &&
                admin_json.has_field("last_name")       && admin_json["last_name"].is_string() &&
                admin_json.has_field("username")        && admin_json["username"].is_string() &&
                admin_json.has_field("email")           && admin_json["email"].is_string()) {
            Admin admin;
            admin.id = admin_json["id"].as_integer();
            admin.first_name = admin_json["first_name"].as_string();
            admin.last_name = admin_json["last_name"].as_string();
            admin.username = admin_json["username"].as_string();
            admin.email = admin_json["email"].as_string();
            if (admin_json.has_field("phone"))
                admin.phone = admin_json["phone"].as_string();
            if (admin_json.has_field("address"))
                admin.address = admin_json["address"].as_string();
            if (admin_json.has_field("country"))
                admin.country = admin_json["country"].as_string();
            if (admin_json.has_field("state_region"))
                admin.state_region = admin_json["state_region"].as_string();
            if (admin_json.has_field("zip"))
                admin.zip = admin_json["zip"].as_string();
            return admin;
        } else {
            return std::nullopt;
        }
    }
};
/// Necessary for comparing if two admins are equal.
inline bool operator==(const Admin &a, const Admin &b) {
    return a.id == b.id &&
           a.first_name == b.first_name &&
           a.last_name == b.last_name &&
           a.username == b.last_name &&
           a.email == b.email &&
           a.phone == b.phone &&
           a.address == b.address &&
           a.country == b.country &&
           a.state_region == b.state_region &&
           a.zip == b.zip;
}
}
#endif // ADMIN_H
