// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#ifndef USER_H
#define USER_H
#include <string>
#include <cpprest/json.h>

namespace aoi_rest {
struct User {
    std::string name;
    int id;
    std::string password;
    web::json::value to_json() {
        auto user_json  = web::json::value::object();
        user_json["name"] = web::json::value::string(name);
        user_json["password"] = web::json::value::string(password);
        return user_json;
    }
};
inline bool operator==(const User &a, const User &b) {
    return a.name == b.name &&
           a.id == b.id &&
           a.password == b.password;
}
}
#endif // USER_H
