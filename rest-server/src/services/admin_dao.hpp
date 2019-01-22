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

    std::vector<Admin> GetAdmins() override;
    std::vector<Admin> GetAdminsByName(const std::string& name) override;
    std::vector<Admin> GetAdminByID(int id) override;
    bool RemoveAdmin(int id) override;
    void AddAdmin(Admin admin, std::string password) override;
    void UpdateAdmin(int id, web::json::object admin_info) override;
    void UpdateAdminPassword(int id, std::string password) override;
  private:
    std::string getEnvVar(std::string const& key) {
        char const* val = getenv(key.c_str()); 
        return val == NULL ? std::string() : std::string(val);
    }
    AdminDao() {
      LoggerInterface& logger(Logger::Instance());
      //TO-DO:(Kris) Use an environment variable instead.
      std::string db_admin_table = getEnvVar("DB_ADMIN_TABLE");
      logger.Log(LogLevel::INFO, "The env db_admin_table is: " + db_admin_table);
      std::string db_password = getEnvVar("DB_PASSWORD");
      logger.Log(LogLevel::INFO, "The env db_password is: " + db_password);
      std::string db_port = getEnvVar("DB_PORT");
      logger.Log(LogLevel::INFO, "The env db_port is: " + db_port);
      std::string db_server = getEnvVar("DB_SERVER");
      logger.Log(LogLevel::INFO, "The env db_server is: " + db_server);
      std::string db_uid = getEnvVar("DB_UID");
      logger.Log(LogLevel::INFO, "The env db_uid is: " + db_uid);
      connStr_ = "Driver={MySQL8Driver};Server="+ db_server +";Port="+ db_port +";Database="+ db_admin_table +";Uid="+ db_uid +";Pwd="+ db_password +";";
    }
    std::vector<Admin> admins__;
    std::string connStr_;
};
}
#endif // ADMIN_DAO_H
