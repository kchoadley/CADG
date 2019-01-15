/// A DAO for users.
/**
 * This data access object adheres to the DataAccessInterface. It is a singleton,
 * accessed through the static method Instance().
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
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
    /// Returns all users.
    /**
     * GetUsers gets all users in the data store.
     * @return Vector of all users.
     */
    std::vector<User> GetUsers() override;
    /// Returns all users that contain the provided name.
    /**
     * GetUsersByName gets all users in the data store which have a name that
     * partially or fully matches the name argument.
     *
     * @param name The name of the user(s) to search for.
     * @return Vector of all users that match the name.
     */
    std::vector<User> GetUsersByName(const std::string& name) override;
    /// Returns all users with the provided id.
    /**
     * GetUserByID gets the user in the data store by id.
     *
     * @param id The id of the user to return.
     * @return Vector containing the found user, or empty if there is no matching user.
     */
    std::vector<User> GetUserByID(int id) override;
    /// Removes a user by the provided id.
    /**
     * RemoveUser removes the user in the data store.
     *
     * @param user The user object to remove.
     * @return Bool indicating successful removal.
     */
    bool RemoveUser(User user) override;
    /// Adds a new user
    /**
     * AddUser adds the user to the data store.
     *
     * @param user The user to add to the data store.
     */
    void AddUser(User user) override;
    /// Updates a user.
    /**
     * UpdateUser updates a user in the data store.
     *
     * @param id The id of the user to update.
     * @param user_info The updated information for the user.
     */
    void UpdateUser(int id, web::json::object user_info) override;
    /**
     * SetConnectionString sets the string used for connecting with the database.
     * @param connStr
     */
    void SetConnectionString(std::string connStr) override;
  private:
    DataAccessObject() { }
    std::vector<User> users__;
    std::string connStr_;
};
}
#endif // DATA_ACCESS_OBJECT_H
