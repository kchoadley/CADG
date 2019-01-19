//
// Created by shulce on 1/19/19.
//

#include <string>
#include <vector>
#include "aog_dao.hpp"
#include "nanodbc.hpp"

namespace cadg_rest {

    AogDao& AogDao::Instance() {
        static AogDao instance;
        return instance;
    }
    void AogDao::SetConnectionString(std::string connStr) {
        connStr_ = connStr;
    }

    std::vector<Aog> AogDao::GetAogs() {
        try {
            nanodbc::connection connection(connStr_);
            nanodbc::result results;
            results = execute(connection, NANODBC_TEXT("select name, aog_id, agency from aog_db.aog;"));
            std::vector<Aog> db_aogs;
            while (results.next()) {
                db_aogs.push_back(Aog {
                        results.get<int>(0, 0)
                        , results.get<std::string>(1, "null_name")
                        , results.get<std::string>(2, "null_agency")});
            }
            return db_aogs;
        } catch (...) {
            std::vector<Aog> db_aogs;
            return db_aogs;
        }
    }

    std::vector<Aog> AogDao::GetAogByName(std::string name) {

        try {
            nanodbc::connection connection(connStr_);
            nanodbc::result results;
            results = execute(connection, NANODBC_TEXT("select name, aog_id, agency from aog_db.aog where name = " + name +";"));
            std::vector<Aog> db_aogs;
            while (results.next()) {
                db_aogs.push_back(Aog {
                        results.get<int>(0, 0)
                        , results.get<std::string>(1, "null_name")
                        , results.get<std::string>(2, "null_agency")});
            }
            return db_aogs;
        } catch (...) {
            std::vector<Aog> db_aogs;
            return db_aogs;
        }
    }

    std::vector<Aog> AogDao::GetAogsByAgency(std::string agency) {
        try {
            nanodbc::connection connection(connStr_);
            nanodbc::result results;
            results = execute(connection, NANODBC_TEXT("select name, aog_id, agency from aog_db.aog where agency = " + agency +";"));
            std::vector<Aog> db_aogs;
            while (results.next()) {
                db_aogs.push_back(Aog {
                        results.get<int>(0, 0)
                        , results.get<std::string>(1, "null_name")
                        , results.get<std::string>(2, "null_agency")});
            }
            return db_aogs;
        } catch (...) {
            std::vector<Aog> db_aogs;
            return db_aogs;
        }
    }

    void AogDao::AddAog(cadg_rest::Aog aog) {

    }
} //end cadg_rest

