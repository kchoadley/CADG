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
    results = execute(connection, NANODBC_TEXT("select username, userId, password from user;"));
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
    nanodbc::connection connection(connStr_);
    nanodbc::statement statement(connection);
    prepare(statement, NANODBC_TEXT("delete from user where userId =?;"));
    statement.bind(0, &user.id);
    execute(statement);
    return true;
}
void DataAccessObject::AddUser(User user) {
    nanodbc::connection connection(connStr_);
    nanodbc::statement statement(connection);
    prepare(statement, NANODBC_TEXT("insert into user (username, password) values(?,?);"));
    nanodbc::string const username = NANODBC_TEXT(user.name);
    statement.bind(0, username.c_str());
    nanodbc::string const password = NANODBC_TEXT(user.password);
    statement.bind(1, password.c_str());
    execute(statement);
    // Get the ID of the newly created user record.
    // Note: LAST_INSERT_ID() is per connection.
    nanodbc::result results;
    results = execute(connection, NANODBC_TEXT("SELECT LAST_INSERT_ID();"));
    int newId = results.get<int>(0,0);
    // Update the user.id if successful.
    if (results.next() && newId > 0) {
      user.id = newId;
    }
}
void DataAccessObject::UpdateUser(int id, web::json::object user_info) {
    // Declare and set nanodbc statement parameters.
    nanodbc::string const username;
    nanodbc::string const password 
    for (auto iter = user_info.cbegin(); iter != user_info.cend(); ++iter) {
        auto &key = iter->first;
        auto &value = iter->second;
        if (key.compare("name") == 0) username = NANODBC_TEXT(value.as_string());
        else if (key.compare("password") == 0) password = NANODBC_TEXT(value.as_string());
    }
    nanodbc::connection connection(connStr_);
    nanodbc::statement statement(connection);
    prepare(statement, NANODBC_TEXT("update user set username = ?, password = ? where userId = ?;"));
    statement.bind(0, username.c_str());
    statement.bind(1, password.c_str());
    statement.bind(2, &id);
    execute(statement);
}
}  // namespace cadg_rest
