// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#include <string>
#include <vector>
#include "data_access_object.hpp"
#include "nanodbc.h"

namespace cadg_rest {
DataAccessObject& DataAccessObject::Instance() {
    static DataAccessObject instance;
    return instance;
}

void DataAccessObject::SetConnectionString(std::string connStr) {
    connStr_ = connStr;
}

std::vector<User> DataAccessObject::GetUsers() {
    nanodbc::connection connection(connStr_);
    nanodbc::result results;
    results = execute(connection, "select first_name || ' ' || last_name as name, id, password from user;");
    std::vector<User> db_users;
    while(results.next()) {
        db_users.push_back(User {
            results.get<std::string>(0, "null_user")
            , results.get<int>(1,0)
	      , results.get<std::string>(2, "null_pw")});
    }
    return db_users;
}
/**
 * Gets user by partial string match of name, ignores case.
 * 
 * TODO: Does not handle a space ' ' in the url correctly. 
 *       Will need to convert '%20' to space ' '.
 * 
 */
std::vector<User> DataAccessObject::GetUsersByName(const std::string& name) {
    std::vector<User> matching_users;
    for (auto& user : users__) {
        if (std::search(user.name.begin(), user.name.end(),
                    name.begin(), name.end(),
                    [](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2);
                    }) != user.name.end()) {
            matching_users.push_back(user);
        }
    }
    return matching_users;
}
/**
 * ID is the primary key of data type User.
 * This method will always return either and empty vector or
 * a vector with 1 User in it. Check returned vector size
 * to determine if there was a User with the associated ID.
 */
std::vector<User> DataAccessObject::GetUserByID(int id) {
    std::vector<User> matching_users;
    for (auto& user : users__) {
        if (user.id == id) {
            matching_users.push_back(user);
            break;
        }
    }
    return matching_users;
}
bool DataAccessObject::RemoveUser(User user) {
    for (auto itr = users__.begin(); itr != users__.end(); itr++) {
        if (user == *itr) {
            users__.erase(itr);
            return true;
        }
    }
    return false;
}
void DataAccessObject::AddUser(User user) {
    users__.push_back(user);
}

void DataAccessObject::UpdateUser(int id, web::json::object user_info) {
    for (auto& user : users__) {
        if (user.id == id) {
            for (auto iter = user_info.cbegin(); iter != user_info.cend(); ++iter) {
                auto &key = iter->first;
                auto &value = iter->second;
                if (key.compare("name") == 0) user.name = value.as_string();
                else if (key.compare("password") == 0) user.password = value.as_string();
            }
            break;
        }
    }
}
}  // namespace cadg_rest
