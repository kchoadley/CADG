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
#include "admin_dao_interface.hpp"
#include "logger.hpp"
#include "log_level.hpp"

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

    std::optional<std::vector<Admin>> GetAdmins() override;
    std::optional<std::vector<Admin>> GetAdminsByName(const std::string& name) override;
    std::optional<std::vector<Admin>> GetAdminByID(int id) override;
    std::optional<bool> RemoveAdmin(int id) override;
    std::optional<bool> AddAdmin(Admin admin) override;
    std::optional<bool> UpdateAdmin(Admin admin) override;
    std::optional<bool> UpdateAdminPassword(int id, std::string password) override;
  private:
    std::string getEnvVar(std::string const& key) {
        char const* val = getenv(key.c_str()); 
        return val == NULL ? std::string() : std::string(val);
    }
    AdminDao() ;
    std::vector<Admin> admins__;
    std::string conn_str__;
    std::string db_admin_table__;
    LoggerInterface& logger;
};
}
#endif // ADMIN_DAO_H
