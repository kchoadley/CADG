/// Implements the DataAccessObject.
/**
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley, Shawn Hulce, Michael McCulley
 *
 * @file        data_access_object.cpp
 * @authors     Kristofer Hoadley, Micheal McCulley
 * @date        November, 2018
 */
#include <string>
#include <vector>
#include "data_access_object.hpp"
#include "nanodbc.hpp"

namespace cadg_rest {
DataAccessObject& DataAccessObject::Instance() {
    static DataAccessObject instance;
    return instance;
}
DataAccessObject::DataAccessObject() : logger(Logger::Instance()) {
        std::string db_test_name__ = getEnvVar("DB_TEST_NAME");
        logger.Log(LogLevel::INFO, "The env db_test_name__ is: " + db_test_name__);
        db_test_table__ = getEnvVar("DB_TEST_TABLE");
        logger.Log(LogLevel::INFO, "The env db_test_table__ is: " + db_test_table__);
        std::string db_password = getEnvVar("DB_PASSWORD");
        logger.Log(LogLevel::INFO, "The env db_password is: " + db_password);
        std::string db_port = getEnvVar("DB_PORT");
        if (db_port.empty()) {
            db_port = "3306";  // default port
        }
        logger.Log(LogLevel::INFO, "The env db_port is: " + db_port);
        std::string db_server = getEnvVar("DB_SERVER");
        if (db_server.empty()) {
            db_server = "127.0.0.1";  // localhost
        }
        logger.Log(LogLevel::INFO, "The env db_server is: " + db_server);
        std::string db_uid = getEnvVar("DB_UID");
        logger.Log(LogLevel::INFO, "The env db_uid is: " + db_uid);
        conn_str__ = "Driver={MySQL8Driver};Server="+ db_server +";Port="+ db_port +";Database="
                + db_test_name__ +";Uid="+ db_uid +";Pwd="+ db_password +";";
        logger.Log(LogLevel::INFO, "The connection string is: " + conn_str__);
}
std::optional<std::vector<User>> DataAccessObject::GetUsers() {
    try {
        nanodbc::connection connection(conn_str__);
        nanodbc::result results;
        results = execute(connection, NANODBC_TEXT("select username, user_id, password from "+ db_test_table__ +";"));
        std::vector<User> db_users;
        while (results.next()) {
            db_users.push_back(User {
                results.get<std::string>(0, "null_user")
                , results.get<int>(1, 0)
                , results.get<std::string>(2, "null_pw")});
        }
        return db_users;
    } catch (std::exception&  e) {
        // return error for testing purposes only
        logger.Log(LogLevel::WARN, e.what(), "DataAccessObject", "GetUsers");
        logger.Log(LogLevel::ERR, "Get Users unable to connect to DB");
        return std::nullopt;
    }
}
/**
 * TODO: Does not handle a space ' ' in the url correctly. 
 *       Will need to convert '%20' to space ' '.
 */
std::optional<std::vector<User>> DataAccessObject::GetUsersByName(const std::string& name) {
    try {
        nanodbc::connection connection(conn_str__);
        nanodbc::result results;
        results = execute(connection, NANODBC_TEXT("select username, user_id, password from "
                + db_test_table__ +" WHERE username LIKE '%"+ name +"%';"));
        std::vector<User> db_users;
        while (results.next()) {
            db_users.push_back(User {
                results.get<std::string>(0, "null_user")
                , results.get<int>(1, 0)
                , results.get<std::string>(2, "null_pw")});
        }
        return db_users;
    } catch (std::exception&  e) {
        // return error for testing purposes only
        logger.Log(LogLevel::WARN, e.what(), "DataAccessObject", "GetUsers");
        logger.Log(LogLevel::ERR, "Get Users unable to connect to DB");
        return std::nullopt;
    }
}
/**
 * ID is the primary key of data type User.
 * This method will always return either and empty vector or
 * a vector with 1 User in it. Check returned vector size
 * to determine if there was a User with the associated ID.
 */
std::optional<std::vector<User>> DataAccessObject::GetUserByID(int id) {
    try {
        nanodbc::connection connection(conn_str__);
        nanodbc::result results;
        results = execute(connection, NANODBC_TEXT("select username, user_id, password from "
                + db_test_table__ +" WHERE user_id="+ std::to_string(id) +";"));
        std::vector<User> db_users;
        while (results.next()) {
            db_users.push_back(User {
                results.get<std::string>(0, "null_user")
                , results.get<int>(1, 0)
                , results.get<std::string>(2, "null_pw")});
        }
        return db_users;
    } catch (std::exception&  e) {
        // return error for testing purposes only
        logger.Log(LogLevel::WARN, e.what(), "DataAccessObject", "GetUsers");
        logger.Log(LogLevel::ERR, "Get Users unable to connect to DB");
        return std::nullopt;
    }
}
std::optional<bool> DataAccessObject::RemoveUser(int id) {
    if (auto user_response = GetUserByID(id)) {
        auto users = user_response.value();
        if (users.empty()) {
            return false;
        } else {
            try {
                nanodbc::connection connection(conn_str__);
                nanodbc::statement statement(connection);
                prepare(statement, NANODBC_TEXT("delete from "+ db_test_table__ +" where user_id =?;"));
                statement.bind(0, &users[0].id);
                execute(statement);
                return true;
            } catch (std::exception&  e) {
                // return error for testing purposes only
                logger.Log(LogLevel::WARN, e.what(), "DataAccessObject", "RemoveUser");
                logger.Log(LogLevel::ERR, "Remove User unable to connect to DB");
                return std::nullopt;
            }
        }
    } else {
        return std::nullopt;
    }
}
std::optional<bool> DataAccessObject::AddUser(User user) {
    logger.Log(LogLevel::INFO, "User name and password: "+ user.name + ", " + user.password);
    try {
        nanodbc::connection connection(conn_str__);
        nanodbc::statement statement(connection);
        prepare(statement, NANODBC_TEXT("insert into "+ db_test_table__ +" (username, password) values(?,?);"));
        nanodbc::string const username = NANODBC_TEXT(user.name);
        statement.bind(0, username.c_str());
        nanodbc::string const password = NANODBC_TEXT(user.password);
        statement.bind(1, password.c_str());
        execute(statement);
        // Get the ID of the newly created user record.
        // Note: LAST_INSERT_ID() is per connection.
        nanodbc::result results;
        results = execute(connection, NANODBC_TEXT("SELECT LAST_INSERT_ID();"));
        results.next();
        int newId = results.get<int>(0, 0);
        logger.Log(LogLevel::DEBUG, "Has id: " + newId);
        // Update the user.id if successful.
        if (results.next() && newId > 0) {
            user.id = newId;
        }
    } catch (std::exception&  e) {
        // return error for testing purposes only
        logger.Log(LogLevel::WARN, e.what(), "DataAccessObject", "AddUser");
        logger.Log(LogLevel::ERR, "Add User unable to connect to DB");
        return std::nullopt;
        // TODO(All): Something?
    }
    return true;
}
std::optional<bool> DataAccessObject::UpdateUser(int id, web::json::object user_info) {
    try {
        // Declare and set nanodbc statement parameters.
        nanodbc::string username;
        nanodbc::string password;
        for (auto iter = user_info.cbegin(); iter != user_info.cend(); ++iter) {
            auto &key = iter->first;
            auto &value = iter->second;
            if (key.compare("name") == 0) username = NANODBC_TEXT(value.as_string());
            else if (key.compare("password") == 0) password = NANODBC_TEXT(value.as_string());
        }
        nanodbc::connection connection(conn_str__);
        nanodbc::statement statement(connection);
        prepare(statement, NANODBC_TEXT("update user set username = ?, password = ? where userId = ?;"));
        statement.bind(0, username.c_str());
        statement.bind(1, password.c_str());
        statement.bind(2, &id);
        execute(statement);
    } catch (std::exception&  e) {
        // return error for testing purposes only
        logger.Log(LogLevel::WARN, e.what(), "DataAccessObject", "UpdateUser");
        logger.Log(LogLevel::ERR, "Update User unable to connect to DB");
        // TODO(All): Something?
    }
    return true;
}

}  // namespace cadg_rest
