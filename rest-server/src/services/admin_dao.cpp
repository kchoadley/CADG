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
std::vector<Admin> AdminDao::GetAdmins() {
    try {
        nanodbc::connection connection(connStr_);
        nanodbc::result results;
        results = execute(connection, NANODBC_TEXT("select adminname, admin_id, password from admin_db.admin;"));
        std::vector<Admin> db_admins;
        while (results.next()) {
            db_admins.push_back(Admin {
                results.get<std::string>(0, "null_admin")
                , results.get<int>(1, 0)
                , results.get<std::string>(2, "null_pw")});
        }
        return db_admins;
    } catch (...) {
        std::vector<Admin> db_admins;
        return db_admins;
    }
}
/**
 * Gets admin by partial string match of name, ignores case.
 * 
 * TODO: Does not handle a space ' ' in the url correctly. 
 *       Will need to convert '%20' to space ' '.
 * 
 */
std::vector<Admin> AdminDao::GetAdminsByName(const std::string& name) {
    std::vector<Admin> matching_admins;
    for (auto& admin : admins__) {
        if (std::search(admin.name.begin(), admin.name.end(),
                    name.begin(), name.end(),
                    [](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2);
                    }) != admin.name.end()) {
            matching_admins.push_back(admin);
        }
    }
    return matching_admins;
}
/**
 * ID is the primary key of data type Admin.
 * This method will always return either and empty vector or
 * a vector with 1 Admin in it. Check returned vector size
 * to determine if there was a Admin with the associated ID.
 */
std::vector<Admin> AdminDao::GetAdminByID(int id) {
    std::vector<Admin> matching_admins;
    for (auto& admin : admins__) {
        if (admin.id == id) {
            matching_admins.push_back(admin);
            break;
        }
    }
    return matching_admins;
}
bool AdminDao::RemoveAdmin(int id) {
    try {
        nanodbc::connection connection(connStr_);
        nanodbc::statement statement(connection);
        prepare(statement, NANODBC_TEXT("delete from admin_db.admin where admin_id =?;"));
        statement.bind(0, &id);
        execute(statement);
        return true;
    } catch (...) {
        return false;
    }
}
void AdminDao::AddAdmin(Admin admin, std::string password) {
    // TODO(All): password either needs to be hashes/salted before it gets here or once it is here.
    try {
        nanodbc::connection connection(connStr_);
        nanodbc::statement statement(connection);
        prepare(statement, NANODBC_TEXT("insert into admin_db.admin (adminname, email, password) values(?,?,?);"));
        nanodbc::string const adminname = NANODBC_TEXT(admin.name);
        statement.bind(0, adminname.c_str());
        nanodbc::string const email = NANODBC_TEXT(admin.email);
        statement.bind(1, email.c_str());
        nanodbc::string const password = NANODBC_TEXT(password);
        statement.bind(2, password.c_str());
        execute(statement);
        // Get the ID of the newly created admin record.
        // Note: LAST_INSERT_ID() is per connection.
        nanodbc::result results;
        results = execute(connection, NANODBC_TEXT("SELECT LAST_INSERT_ID();"));
        int newId = results.get<int>(0, 0);
        // Update the admin.id if successful.
        if (results.next() && newId > 0) {
            admin.id = newId;
        }
    } catch (...) {
        // TODO(All): Something?
    }
}

void AdminDao::UpdateAdminPassword(int id, std::string password) {
    // TODO(All): password either needs to be hashes/salted before it gets here or once it is here.
    try {
        // Declare and set nanodbc statement parameters.
        nanodbc::string password = NANODBC_TEXT(password);
        nanodbc::connection connection(connStr_);
        nanodbc::statement statement(connection);
        prepare(statement, NANODBC_TEXT("update admin set password = ? where adminId = ?;"));
        statement.bind(0, password.c_str());
        statement.bind(1, &id);
        execute(statement);
    } catch (...) {
        // TODO(All): Something?
    }
}
void AdminDao::UpdateAdmin(int id, web::json::object admin_info) {
    try {
        // Declare and set nanodbc statement parameters.
        nanodbc::string adminname;
        nanodbc::string email;
        for (auto iter = admin_info.cbegin(); iter != admin_info.cend(); ++iter) {
            auto &key = iter->first;
            auto &value = iter->second;
            if (key.compare("name") == 0) adminname = NANODBC_TEXT(value.as_string());
            else if (key.compare("email") == 0) email = NANODBC_TEXT(value.as_string());
        }
        nanodbc::connection connection(connStr_);
        nanodbc::statement statement(connection);
        prepare(statement, NANODBC_TEXT("update admin set adminname = ?, email = ? where adminId = ?;"));
        statement.bind(0, adminname.c_str());
        statement.bind(1, email.c_str());
        statement.bind(2, &id);
        execute(statement);
    } catch (...) {
        // TODO(All): Something?
    }
}
}  // namespace cadg_rest
