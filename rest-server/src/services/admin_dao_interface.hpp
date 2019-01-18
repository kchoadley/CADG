// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/// An interface for an admin DAO.
/**
 * This defines the interface for a data access object (DAO) which is
 * used to provide CRUD operations on a data storage of admins.
 *
 * @file        admin_dao_interface.hpp
 * @authors     Kristofer Hoadley
 * @date        November, 2018
 */
#ifndef ADMIN_DAO_INTERFACE_H
#define ADMIN_DAO_INTERFACE_H
#include <string>
#include <vector>
#include "admin.hpp"

namespace cadg_rest {
/**
 * DataAccessInterface defines several CRUD operations for a admin data store.
 * This interface must be defines in an inheriting class.
 */
class AdminDaoInterface {
  public:
    /**
     * GetAdmins gets all admins in the data store.
     * 
     * @return Vector of all admins.
     */
    virtual std::vector<Admin> GetAdmins() = 0;
    /**
     * GetAdminsByName gets all admins in the data store which have a name that
     * partially or fully matches the name argument.
     * 
     * @param name The name of the admin(s) to search for.
     * @return Vector of all admins that match the name.
     */
    virtual std::vector<Admin> GetAdminsByName(const std::string& name) = 0;
    /**
     * GetAdminByID gets the admin in the data store by id.
     * 
     * @param id The id of the admin to return.
     * @return Vector containing the found admin, or empty if there is no matching admin.
     */
    virtual std::vector<Admin> GetAdminByID(int id) = 0;
    /**
     * RemoveAdmin removes the admin in the data store by id.
     * 
     * @param id The id of the admin to remove.
     * @return Bool indicating successful removal.
     */
    virtual bool RemoveAdmin(int id) = 0;
    /**
     * AddAdmin adds the admin to the data store.
     * 
     * @param admin The admin to add to the data store.
     */
    virtual void AddAdmin(Admin admin, std::string password) = 0;
    /**
     * UpdateAdmin updates a admin in the data store.
     * 
     * @param id The id of the admin to update.
     * @param admin_info The updated information for the admin.
     */
    virtual void UpdateAdmin(int id, web::json::object admin_info) = 0;
    /**
     * UpdateAdminPassword updates an admin's password in the data store.
     * 
     * @param id The id of the admin to update.
     * @param password The new password.
     */
    virtual void UpdateAdminPassword(int id, std::string password) = 0;
};
}
#endif // ADMIN_DAO_INTERFACE_H
