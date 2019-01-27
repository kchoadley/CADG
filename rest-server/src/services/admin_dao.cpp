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
    try {
        nanodbc::connection connection(conn_str__);
        nanodbc::result results = execute(connection, NANODBC_TEXT(
                std::string("select id, first_name, last_name, username, email, ") +
                std::string("phone, address, country, state_region, zip from ") +
                db_admin_table__ + ";"));
        std::vector<Admin> db_admins;
        while (results.next()) {
            db_admins.push_back(Admin {
                results.get<int>(0, 0),
                results.get<std::string>(1, ""),
                results.get<std::string>(2, ""),
                results.get<std::string>(3, ""),
                results.get<std::string>(4, ""),
                results.get<std::string>(5, ""),
                results.get<std::string>(6, ""),
                results.get<std::string>(7, ""),
                results.get<std::string>(8, ""),
                results.get<std::string>(9, "")});
        }
        return db_admins;
    } catch (std::exception&  e) {
        logger.Log(LogLevel::ERR, e.what(), "AdminDao", "GetAdmins");
        return std::nullopt;
    }
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
    logger.Log(LogLevel::INFO, "AdminDao", "AddAdmin", std::string("Admin id: ")+ std::to_string(admin.id) +
                                                    ", first_name: "+ admin.first_name +
                                                    ", last_name: "+ admin.first_name +
                                                    ", username: "+ admin.username +
                                                    ", email: "+ admin.email +
                                                    ", phone: "+ admin.phone +
                                                    ", address: "+ admin.address +
                                                    ", country: "+ admin.country +
                                                    ", state_region: "+ admin.state_region +
                                                    ", zip: "+ admin.zip);
    try {
        nanodbc::connection connection(conn_str__);
        nanodbc::statement statement(connection);
        prepare(statement, NANODBC_TEXT("insert into "+ db_admin_table__ +
                " (first_name, last_name, username, email, phone, address, country, state_region, zip, password)"+
                " values(?,?,?,?,?,?,?,?,?,?);"));
        nanodbc::string const first_name = NANODBC_TEXT(admin.first_name);
        statement.bind(0, first_name.c_str());
        nanodbc::string const last_name = NANODBC_TEXT(admin.last_name);
        statement.bind(1, last_name.c_str());
        nanodbc::string const username = NANODBC_TEXT(admin.username);
        statement.bind(2, username.c_str());
        nanodbc::string const email = NANODBC_TEXT(admin.email);
        statement.bind(3, email.c_str());
        nanodbc::string const phone = NANODBC_TEXT(admin.phone);
        statement.bind(4, phone.c_str());
        nanodbc::string const address = NANODBC_TEXT(admin.address);
        statement.bind(5, address.c_str());
        nanodbc::string const country = NANODBC_TEXT(admin.country);
        statement.bind(6, country.c_str());
        nanodbc::string const state_region = NANODBC_TEXT(admin.state_region);
        statement.bind(7, state_region.c_str());
        nanodbc::string const zip = NANODBC_TEXT(admin.zip);
        statement.bind(8, zip.c_str());
        nanodbc::string const password = NANODBC_TEXT(password);
        statement.bind(9, password.c_str());
        // TODO(ALL): Verify the DB inserted successfully (check return value of execute).
        execute(statement);
        // Get the ID of the newly created admin record.
        // Note: LAST_INSERT_ID() is per connection.
        nanodbc::result results;
        results = execute(connection, NANODBC_TEXT("SELECT LAST_INSERT_ID();"));
        results.next();
        int newId = results.get<int>(0, 0);
        logger.Log(LogLevel::DEBUG, "Has id: " + newId);
        // Update the admin.id if successful.
        if (results.next() && newId > 0) {
            admin.id = newId;
        }
    } catch (std::exception&  e) {
        logger.Log(LogLevel::ERR, e.what(), "AdminDao", "AddAdmin");
        return std::nullopt;
    }
    return true;
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
