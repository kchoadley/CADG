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
bool Requery() {
    try {
        nanodbc::connection connection(conn_str_);
        nanodbc::result results;
        results = execute(connection, NANODBC_TEXT("select id, name, type, format, ip from cadg.disseminator;"));
        std::vector<Disseminator> temp_disseminators;
        while (results.next()) {
            Disseminator temp;
            temp.id = results.get<int>(0,0);
            temp.name = results.get<std::string>(1,"");
            temp.type = results.get<std::string>(2,"");
            temp.format = results.get<std::string>(3,"");
            temp.ip = results.get<std::string>(4,"");
            temp_disseminators.push_back(temp);
        }
        disseminators__ = temp_disseminators;
        return true;
    } catch (...) {
        return false;
    }
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
        nanodbc::connection connection(conn_str_);
        nanodbc::statement statement(connection);
        prepare(statement, NANODBC_TEXT("delete from cadg.disseminator where disseminator_id =?;"));
        statement.bind(0, &id);
        execute(statement);
        return true;
    } catch (...) {
        return false;
    }
}
bool DisseminatorDao::AddDisseminator(Disseminator disseminator) {
    try {
        nanodbc::connection connection(conn_str_);
        nanodbc::statement statement(connection);
        prepare(statement, NANODBC_TEXT("insert into cadg.disseminator (name, type, format, ip) values (?,?,?,?);");
        nanodbc::string const name = NANODBC_TEXT(disseminator.name);
        statement.bind(0, name.c_str());
        nanodbc::string const type = NANODBC_TEXT(disseminator.type);
        statement.bind(1, type.c_str());
        nanodbc::string const format = NANODBC_TEXT(disseminator.format);
        statement.bind(2, format.c_str());
        nanodbc::string const ip = NANODBC_TEXT(disseminator.ip);
        statement.bind(3, ip.c_str());
        execute(statement);
        // Get the ID of the newly created user record.
        nanodbc::result results;
        results = execute(connection, NANODBC_TEXT("SELECT LAST_INSERT_ID();"));
        results.next();
        int new_id = results.get<int>(0, 0);
        if (new_id > 0) {
            disseminator.id = new_id;
            disseminators__.push_back(disseminator);
            return true;
        }
    } catch (std::exception&  e) {
        return false;
    }
}


bool DisseminatorDao::UpdateDisseminator(Disseminator disseminator) {
    try {
        nanodbc::connection connection(conn_str_);
        nanodbc::statement statement(connection);
        prepare(statement, NANODBC_TEXT("update cadg.disseminator set name = ?, type = ?, format = ?, ip = ? where id = ?;")
        nanodbc::string const name = NANODBC_TEXT(disseminator.name);
        statement.bind(0, name.c_str());
        nanodbc::string const type = NANODBC_TEXT(disseminator.type);
        statement.bind(1, type.c_str());
        nanodbc::string const format = NANODBC_TEXT(disseminator.format);
        statement.bind(2, format.c_str());
        nanodbc::string const ip = NANODBC_TEXT(disseminator.ip);
        statement.bind(3, ip.c_str());
		nanodbc::string const id = NANODBC_TEXT(disseminator.id);
		statement.bind(4, id.c_str());
        execute(statement);
        for (auto& temp : disseminators__) {
            if (temp.id == disseminator.id) {
                temp.name = disseminator.name;
                temp.type = disseminator.type;
                temp.format = disseminator.format;
                temp.ip = disseminator.ip;
                break;
            }
        }
        return true;
    } catch (std::exception&  e) {
        return false;
    }
}
}  // namespace cadg_rest

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
