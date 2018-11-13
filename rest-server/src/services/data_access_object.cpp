// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#include <string>
#include <vector>
#include "data_access_object.hpp"

namespace cadg_rest {
DataAccessObject& DataAccessObject::Instance() {
    static DataAccessObject instance;
    return instance;
}
std::vector<User> DataAccessObject::GetUsers() {
    return users__;
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
}  // namespace aoi_rest
