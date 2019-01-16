/// An interface for a DAO for users.
/**
 * This defines the interface for a data access object (DAO) which is
 * used to provide CRUD operations on a data storage of Users.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 *
 * @file        data_access_interface.hpp
 * @authors     Kristofer Hoadley
 * @date        November, 2018
 */
#ifndef DATA_ACCESS_INTERFACE_H
#define DATA_ACCESS_INTERFACE_H
#include <optional>
#include <string>
#include <vector>
#include "user.hpp"
#include "aog.hpp"

namespace cadg_rest {
/**
 * DataAccessInterface defines several CRUD operations for a user data store.
 * This interface must be defines in an inheriting class.
 */
class DataAccessInterface {
  public:
    /// Returns all users.
    /**
     * GetUsers gets all users in the data store.
     * @return Vector of all users.
     */
    virtual std::optional<std::vector<User>> GetUsers() = 0;
    /// Returns all users that contain the provided name.
    /**
     * GetUsersByName gets all users in the data store which have a name that
     * partially or fully matches the name argument.
     * 
     * @param name The name of the user(s) to search for.
     * @return Vector of all users that match the name.
     */
    virtual std::optional<std::vector<User>> GetUsersByName(const std::string& name) = 0;
    /// Returns all users with the provided id.
    /**
     * GetUserByID gets the user in the data store by id.
     * 
     * @param id The id of the user to return.
     * @return Vector containing the found user, or empty if there is no matching user.
     */
    virtual std::optional<std::vector<User>> GetUserByID(int id) = 0;
    /// Removes a user by the provided id.
    /**
     * RemoveUser removes the user in the data store by id.
     * 
     * @param user The user object to remove.
     * @return Bool indicating successful removal.
     */
    virtual std::optional<bool> RemoveUser(int id) = 0;
    /// Adds a new user
    /**
     * AddUser adds the user to the data store.
     * 
     * @param user The user to add to the data store.
     */
    virtual std::optional<bool> AddUser(User user) = 0;
    /// Updates a user.
    /**
     * UpdateUser updates a user in the data store.
     * 
     * @param id The id of the user to update.
     * @param user_info The updated information for the user.
     */

    virtual std::optional<bool> UpdateUser(int id, web::json::object user_info) = 0;

    virtual void UpdateUser(int id, web::json::object user_info) = 0;
    /**
     * SetConnectionString sets the string used for connecting with the database.
     * 
     * @param connStr
     */


};
}
#endif // DATA_ACCESS_INTERFACE_H
