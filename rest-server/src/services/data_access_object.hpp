// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/// A DAO for users.
/**
 * This data access object adheres to the DataAccessInterface. It is a singleton,
 * accessed through the static method Instance().
 *
 * @file        data_access_object.hpp
 * @authors     Kristofer Hoadley
 * @date        November, 2018
 */
#ifndef DATA_ACCESS_OBJECT_H
#define DATA_ACCESS_OBJECT_H
#include <string>
#include <vector>
#include "user.hpp"
#include "data_access_interface.hpp"
#include "logger.hpp"
#include "log_level.hpp"

namespace cadg_rest {
/// A DAO for users.
/**
 * DataAccessObject implements CRUD operations on the user data store.
 */
class DataAccessObject : public DataAccessInterface {
  public:
    /// Instance returns a reference to the DataAccessObject.
    /**
     * Instance implements the Singleton design pattern.
     */
    static DataAccessObject& Instance();
    /// Deletes the copy constructor to enforce singleton.
    DataAccessObject(DataAccessObject const&) = delete;
    /// Deletes the assignment constructor to enforce singleton.
    void operator=(DataAccessObject const&) = delete;

    std::optional<std::vector<User>> GetUsers() override;
    std::optional<std::vector<User>> GetUsersByName(const std::string& name) override;
    std::optional<std::vector<User>> GetUserByID(int id) override;
    std::optional<bool> RemoveUser(int id) override;
    std::optional<bool> AddUser(User user) override;
    std::optional<bool> UpdateUser(int id, web::json::object user_info) override;
  private:
    std::string getEnvVar(std::string const& key) {
        char const* val = getenv(key.c_str()); 
        return val == NULL ? std::string() : std::string(val);
    }
    DataAccessObject();
    std::vector<User> users__;
    std::string conn_str__;
    std::string db_test_table__;
    LoggerInterface& logger;
};
}
#endif // DATA_ACCESS_OBJECT_H
