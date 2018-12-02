// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/**
 * Contains a user data struct for moving user data to/from
 * a data store and a REST endpoint.
 *
 * @file        controller.cpp
 * @authors     Kristofer Hoadley
 * @date        November, 2018
 */
#ifndef USER_H
#define USER_H
#include <string>
#include <cpprest/json.h>

namespace cadg_rest {
/**
 * A user struct which contains a name, id, and password.
 */
struct User {
    std::string name;
    int id;
    std::string password;
    /**
     * Converts the user struct to a json object.
     * 
     * The id of the user is to be set to the object name.
     * 
     * @return a json object representation of a user.
     * 
     */
    web::json::value to_json() {
        auto user_json  = web::json::value::object();
        user_json["name"] = web::json::value::string(name);
        user_json["password"] = web::json::value::string(password);
        return user_json;
    }
};
/// Necessary for comparing if two users are equal.
inline bool operator==(const User &a, const User &b) {
    return a.name == b.name &&
           a.id == b.id &&
           a.password == b.password;
}
}
#endif // USER_H
