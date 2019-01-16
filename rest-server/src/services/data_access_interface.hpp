// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/// An interface for a DAO for users.
/**
 * This defines the interface for a data access object (DAO) which is
 * used to provide CRUD operations on a data storage of Users.
 *
 * @file        data_access_interface.hpp
 * @authors     Kristofer Hoadley
 * @date        November, 2018
 */
#ifndef DATA_ACCESS_INTERFACE_H
#define DATA_ACCESS_INTERFACE_H
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
    /**
     * GetUsers gets all users in the data store.
     * 
     * @return Vector of all users.
     */
    virtual std::vector<User> GetUsers() = 0;
    /**
     * GetUsersByName gets all users in the data store which have a name that
     * partially or fully matches the name argument.
     * 
     * @param name The name of the user(s) to search for.
     * @return Vector of all users that match the name.
     */
    virtual std::vector<User> GetUsersByName(const std::string& name) = 0;
    /**
     * GetUserByID gets the user in the data store by id.
     * 
     * @param id The id of the user to return.
     * @return Vector containing the found user, or empty if there is no matching user.
     */
    virtual std::vector<User> GetUserByID(int id) = 0;
    /**
     * RemoveUser removes the user in the data store by id.
     * 
     * @param id The id of the user to remove.
     * @return Bool indicating successful removal.
     */
    virtual bool RemoveUser(User user) = 0;
    /**
     * AddUser adds the user to the data store.
     * 
     * @param user The user to add to the data store.
     */
    virtual void AddUser(User user) = 0;
    /**
     * UpdateUser updates a user in the data store.
     * 
     * @param id The id of the user to update.
     * @param user_info The updated information for the user.
     */
    virtual void UpdateUser(int id, web::json::object user_info) = 0;
    /**
     * SetConnectionString sets the string used for connecting with the database.
     * 
     * @param connStr
     */

    virtual std::vector<Aog> GetAogs() = 0;

    virtual std::vector<Aog> GetAogByName(std::string name) = 0;

    // TO-DO(Mike): This method, SetConnectionString, should be in the inheriting class.
    // TO-DO(Mike): connStr should be conn_str.
    virtual void SetConnectionString(std::string connStr) = 0;
};
}
#endif // DATA_ACCESS_INTERFACE_H
