// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/**
 * Implementation of AdminDao.
 *
 * @file        admin_dao.cpp
 * @authors     Kristofer Hoadley, Micheal McCulley
 * @date        November, 2018
 */
#include <string>
#include <vector>
#include "admin_dao.hpp"
#include "nanodbc.hpp"

namespace cadg_rest {
AdminDao& AdminDao::Instance() {
    static AdminDao instance;
    return instance;
}
AdminDao::AdminDao() : logger(Logger::Instance()) {
        std::string db_admin_name__ = getEnvVar("DB_ADMIN_NAME");
        logger.Log(LogLevel::INFO, "The env db_admin_name__ is: " + db_admin_name__);
        db_admin_table__ = getEnvVar("DB_ADMIN_TABLE");
        logger.Log(LogLevel::INFO, "The env db_admin_table__ is: " + db_admin_table__);
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
                + db_admin_name__ +";Uid="+ db_uid +";Pwd="+ db_password +";";
        logger.Log(LogLevel::INFO, "The connection string is: " + conn_str__);
}
std::optional<std::vector<Admin>> AdminDao::GetAdmins() {
    // TODO(Kris): implement GetAdmins
    return std::nullopt;
}
std::optional<std::vector<Admin>> AdminDao::GetAdminsByName(const std::string& name) {
    // TODO(Kris): implement GetAdminsByName
    return std::nullopt;
}
std::optional<std::vector<Admin>> AdminDao::GetAdminByID(int id) {
    // TODO(Kris): implement GetAdminByID
    return std::nullopt;
}
std::optional<bool> AdminDao::RemoveAdmin(int id) {
    // TODO(Kris): implement RemoveAdmin
    return std::nullopt;
}
std::optional<bool> AdminDao::AddAdmin(Admin admin, std::string password) {
    // TODO(Kris): implement AddAdmin
    return std::nullopt;
}

std::optional<bool> AdminDao::UpdateAdminPassword(int id, std::string password) {
    // TODO(Kris): implement UpdateAdminPassword
    return std::nullopt;
}
std::optional<bool> AdminDao::UpdateAdmin(Admin admin_info) {
    // TODO(Kris): implement UpdateAdmin
    return std::nullopt;
}
}  // namespace cadg_rest
