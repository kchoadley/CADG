/**
 *  Alert Originator Groups Data Access
 *
 * Copyright 2019   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley, Shawn Hulce, Michael McCulley
 *
 * @file        aog_dao.cpp
 * @authors     Shawn Hulce
 * @date        January 2019
 */

#include <string>
#include <vector>
#include "aog_dao.hpp"
#include "nanodbc.hpp"

namespace cadg_rest {

    AogDao::AogDao() : logger(Logger::Instance()) {
        std::string db_password = getEnvVar("DB_PASSWORD");
        logger.Log(LogLevel::INFO, "The env db_password is: " + db_password);
        if (db_password.empty()) {
            db_password = "example";
        }
        std::string db_port = getEnvVar("DB_PORT");
        if (db_port.empty()) {
            db_port = "3306";  // default port
        }
        logger.Log(LogLevel::INFO, "The env db_port is: " + db_port);
        std::string db_server = getEnvVar("DB_SERVER");
        if (db_server.empty()) {
            db_server = "cadg-db";  // localhost
        }
        logger.Log(LogLevel::INFO, "The env db_server is: " + db_server);
        std::string db_uid = getEnvVar("DB_UID");
        if (db_uid.empty()) {
            db_uid = "root";
        }
        logger.Log(LogLevel::INFO, "The env db_uid is: " + db_uid);
        connStr_ = "Driver={MySQL8Driver};Server="+ db_server +";Port="+ db_port +";Database=cadg;Uid="+ db_uid +";Pwd="+ db_password +";";
        logger.Log(LogLevel::INFO, "The AogDao connection string is: " + connStr_);
    }

    AogDao& AogDao::Instance() {
        static AogDao instance;
        return instance;
    }
    void AogDao::SetConnectionString(std::string connStr) {
        connStr_ = connStr;
    }

    std::optional<std::vector<Aog>> AogDao::GetAogs() {
        try {
            nanodbc::connection connection(connStr_);
            nanodbc::result results;
            results = execute(connection, NANODBC_TEXT(
                    "select originator_id, originator_name, agency from cadg.originator;"));
            std::vector<Aog> db_aogs;
            while (results.next()) {
                db_aogs.push_back(Aog {
                        results.get<int>(0, 0)
                        , results.get<std::string>(1, "null_name")
                        , results.get<std::string>(2, "null_agency")});
            }
            return db_aogs;
        } catch (...) {
            return std::nullopt;
        }
    }

    std::optional<std::vector<Aog>> AogDao::GetAogByName(std::string name) {
        try {
            nanodbc::connection connection(connStr_);
            nanodbc::result results;
            results = execute(connection, NANODBC_TEXT(
                    "select originator_id, originator_name, agency from cadg.originator where originator_name like '%" +
                    name +"%';"));
            std::vector<Aog> db_aogs;
            while (results.next()) {
                logger.Log(LogLevel::DEBUG, results.get<std::string>(1), "AogDao", "GetAogByName");
                db_aogs.push_back(Aog {
                        results.get<int>(0, 0)
                        , results.get<std::string>(1, "null_name")
                        , results.get<std::string>(2, "null_agency")});
            }
            if (db_aogs.size() > 0) {
                return db_aogs;
            } else {
                return std::nullopt;
            }
        } catch (...) {
            return std::nullopt;
        }
    }

    std::optional<std::vector<Aog>> AogDao::GetAogsByAgency(std::string agency) {
        try {
            nanodbc::connection connection(connStr_);
            nanodbc::result results;
            results = execute(connection, NANODBC_TEXT(
                    "select originator_id, originator_name, agency from cadg.originator where agency like '%" +
                    agency +"%';"));
            std::vector<Aog> db_aogs;
            while (results.next()) {
                db_aogs.push_back(Aog {
                        results.get<int>(0, 0)
                        , results.get<std::string>(1, "null_name")
                        , results.get<std::string>(2, "null_agency")});
            }
            if (db_aogs.size() > 0) {
                return db_aogs;
            } else {
                return std::nullopt;
            }
        } catch (...) {
            return std::nullopt;
        }
    }

    std::optional<std::vector<Aog>> AogDao::GetAogById(int id) {
        try {
            nanodbc::connection connection(connStr_);
            nanodbc::result results;
            std::vector<Aog> aogs;
            results = execute(connection, NANODBC_TEXT(
                    "select originator_id, originator_name, agency from cadg.originator where originator_id = " +
                    std::to_string(id)));
            while (results.next()) {
                aogs.push_back(Aog {
                        results.get<int>(0, 0),
                        results.get<std::string>(1, "null_name"),
                        results.get<std::string>(2, "null_agency")});
            }
            if (aogs.size() > 0) {
                return aogs;
            } else {
                return std::nullopt;
            }
        } catch (std::exception& e) {
            logger.Log(LogLevel::WARN, e.what(), "AogDao", "GetAogById");
            return std::nullopt;
        }
    }

    std::optional<bool> AogDao::AddAog(cadg_rest::Aog aog) {
        try {
            logger.Log(LogLevel::DEBUG, "Aog to Add: " + aog.name + " " + aog.agency, "AogDao", "AddAog");
            nanodbc::connection connection(connStr_);
            nanodbc::statement statement(connection);
            prepare(statement, NANODBC_TEXT("insert into cadg.originator (originator_name, agency) values(?,?);"));
            nanodbc::result results;
            nanodbc::string const originator_name = NANODBC_TEXT(aog.name);
            statement.bind(0, originator_name.c_str());
            nanodbc::string const agency = NANODBC_TEXT(aog.agency);
            statement.bind(1, agency.c_str());
            execute(statement);
            return true;
        } catch (std::exception& e) {
            logger.Log(LogLevel::WARN, e.what(), "AogDao", "AddAog");
            return std::nullopt;
        }
    }

    std::optional<bool> AogDao::UpdateAog(Aog aog) {
        try {
            nanodbc::connection connection(connStr_);
            nanodbc::statement statement(connection);
            prepare(statement, NANODBC_TEXT(
                    "update cadg.originator set originator_name=?, agency=? where originator_id=?;"));
            nanodbc::result results;
            nanodbc::string const originator_name = NANODBC_TEXT(aog.name);
            statement.bind(0, originator_name.c_str());
            nanodbc::string const agency = NANODBC_TEXT(aog.agency);
            statement.bind(1, agency.c_str());
            const int *originator_id = &aog.id;
            statement.bind(2, originator_id);
            execute(statement);
            return true;
        } catch (std::exception& e) {
            logger.Log(LogLevel::WARN, e.what(), "AogDao", "UpdateAog");
            return std::nullopt;
        }
    }

    std::optional<bool> AogDao::DeleteAog(int id) {
        try {
            nanodbc::connection connection(connStr_);
            nanodbc::statement statement(connection);
            prepare(statement, NANODBC_TEXT("delete from cadg.originator where originator_id=?;"));
            const int *originator_id = &id;
            statement.bind(0, originator_id);
            execute(statement);
            return true;
        } catch (std::exception& e) {
            logger.Log(LogLevel::WARN, e.what(), "AogDao", "DeleteAog");
            return std::nullopt;
        }
    }
}  // namespace cadg_rest

