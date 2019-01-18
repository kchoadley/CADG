// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/// A DAO for admins.
/**
 * This data access object adheres to the AdminDaoInterface. It is a singleton,
 * accessed through the static method Instance().
 *
 * @file        admin_dao.hpp
 * @authors     Kristofer Hoadley
 * @date        November, 2018
 */
#ifndef ADMIN_DAO_H
#define ADMIN_DAO_H
#include <string>
#include <vector>
#include "admin.hpp"
#include "admin_dao_interface.hpp"

namespace cadg_rest {
/// A DAO for admins.
/**
 * AdminDao implements CRUD operations on the admin data store.
 */
class AdminDao : public AdminDaoInterface {
  public:
    /// Instance returns a reference to the AdminDao.
    /**
     * Instance implements the Singleton design pattern.
     */
    static AdminDao& Instance();
    /// Deletes the copy constructor to enforce singleton.
    AdminDao(AdminDao const&) = delete;
    /// Deletes the assignment constructor to enforce singleton.
    void operator=(AdminDao const&) = delete;

    std::vector<Admin> GetAdmins() override;
    std::vector<Admin> GetAdminsByName(const std::string& name) override;
    std::vector<Admin> GetAdminByID(int id) override;
    bool RemoveAdmin(int id) override;
    void AddAdmin(Admin admin, std::string password) override;
    void UpdateAdmin(int id, web::json::object admin_info) override;
    void UpdateAdminPassword(int id, std::string password) override;
  private:
    AdminDao() {
      //TO-DO:(Kris) Use an environment variable instead.
      connStr_ = "this will be the actual connection string";
    }
    std::vector<Admin> admins__;
    std::string connStr_;
};
}
#endif // ADMIN_DAO_H
