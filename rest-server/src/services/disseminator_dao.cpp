// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/**
 * Implementation of DisseminatorDao.
 *
 * @file        disseminator_dao.cpp
 * @authors     Michael McCulley
 * @date        January, 2019
 */
#include <string>
#include <vector>
#include "disseminator_dao.hpp"
#include "disseminator_endpoint.hpp"
#include "nanodbc.hpp"

namespace cadg_rest {
DisseminatorDao& DisseminatorDao::Instance() {
    static DisseminatorDao instance;
    return instance;
}
void DisseminatorDao::SetConnectionString(std::string conn_str) {
    conn_str_ = conn_str;
}
std::vector<Disseminator> DisseminatorDao::GetDisseminators() {
    return disseminators__;
}
/**
 * Gets disseminator by partial string match of name, ignores case.
 * 
 * TODO: Does not handle a space ' ' in the url correctly. 
 *       Will need to convert '%20' to space ' '.
 * 
 */
std::vector<Disseminator> DisseminatorDao::GetDisseminatorsByName(const std::string& name) {
    std::vector<Disseminator> matching_disseminators;
    for (auto& disseminator : disseminators__) {
        if (std::search(disseminator.name.begin(), disseminator.name.end(),
                    name.begin(), name.end(),
                    [](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2);
                    }) != disseminator.name.end()) {
            matching_disseminators.push_back(disseminator);
        }
    }
    return matching_disseminators;
}
/**
 * ID is the primary key of data type Disseminator.
 * This method will always return either and empty vector or
 * a vector with 1 Disseminator in it. Check returned vector size
 * to determine if there was a Disseminator with the associated ID.
 */
std::vector<Disseminator> DisseminatorDao::GetDisseminatorByID(int id) {
    std::vector<Disseminator> matching_disseminators;
    for (auto& disseminator : disseminators__) {
        if (disseminator.id == id) {
            matching_disseminators.push_back(disseminator);
            break;
        }
    }
    return matching_disseminators;
}
bool DisseminatorDao::RemoveDisseminator(int id) {
    try {
        nanodbc::connection connection(connStr_);
        nanodbc::statement statement(connection);
        prepare(statement, NANODBC_TEXT("delete from disseminator_db.disseminator where disseminator_id =?;"));
        statement.bind(0, &id);
        execute(statement);
        return true;
    } catch (...) {
        return false;
    }
}
void DisseminatorDao::AddDisseminator(Disseminator disseminator) {
    disseminators__.push_back(disseminator);
    // TODO(Mike): Write to DB.
}


void DisseminatorDao::UpdateDisseminator(int id, web::json::object disseminator_info) {
    try {
        // Declare and set nanodbc statement parameters.
        nanodbc::string name;
        nanodbc::string email;
        for (auto iter = disseminator_info.cbegin(); iter != disseminator_info.cend(); ++iter) {
            auto &key = iter->first;
            auto &value = iter->second;
            if (key.compare("name") == 0) disseminatorname = NANODBC_TEXT(value.as_string());
            else if (key.compare("email") == 0) email = NANODBC_TEXT(value.as_string());
        }
        nanodbc::connection connection(connStr_);
        nanodbc::statement statement(connection);
        prepare(statement, NANODBC_TEXT("update disseminator set name = ?, email = ? where dissseminator_id = ?;"));
        statement.bind(0, disseminatorname.c_str());
        statement.bind(1, email.c_str());
        statement.bind(2, &id);
        execute(statement);
    } catch (...) {
        // TODO(All): Something?
    }
}
}  // namespace cadg_rest
