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

    /// User handling methods
    std::vector<User> GetUsers() override;
    std::vector<User> GetUsersByName(const std::string& name) override;
    std::vector<User> GetUserByID(int id) override;
    bool RemoveUser(User user) override;
    void AddUser(User user) override;
    void UpdateUser(int id, web::json::object user_info) override;
    void SetConnectionString(std::string connStr) override;

    /// AOG handling methods
    std::vector<Aog> GetAogs() override;
    std::vector<Aog> GetAogByName(std::string name) override;

  private:
    DataAccessObject() { }
    std::vector<User> users__;
    std::string connStr_;
};
}
#endif // DATA_ACCESS_OBJECT_H
