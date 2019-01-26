/// Implements the AlertDao.
/**
 * Implementation of AlertDao.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley
 *                  Shawn Hulce, Michael McCulley
 *
 * @file    alert_dao.cpp
 * @authors Vaniya Agrawal
 * @date    January, 2019
 */

#include <string>
#include <vector>
#include "alert_dao.hpp"
#include "nanodbc.hpp"

namespace cadg_rest {
    AlertDao& AlertDao::Instance() {
        static AlertDao instance;
        return instance;
    }
    AdminDao::AdminDao() : logger(Logger::Instance()) {
        db_alert_table__ = "cadg.message";
//        conn_str__ = "Driver={MySQL8Driver};Server="+ db_server +";Port="+ db_port +";Database="
//                     + db_admin_name__ +";Uid="+ db_uid +";Pwd="+ db_password +";";
    }
    std::opctional<std::vector<Alert>> AlertDao::GetAlerts() {
        try {
            nanodbc::connection connection(conn_str__);
            nanodbc::result results = execute(connection, NANODBC_TEXT(
                    std::string("select message_id, identifier, originator_id, message_type, scope, status, ") +
                    std::string("urgency, severity, sent_time, cap_xml from ") +
                    db_alert_table__ + ";"));
            std::vector<Alert> db_alerts;
            while (results.next()) {
                db_alerts.push_back(Alert{
                    results.get<int>(0, 0),
                    results.get<std::string>(1, ""),
                    results.get<int>(2, 0),
                    results.get<std::string>(3, ""),
                    results.get<std::string>(4, ""),
                    results.get<std::string>(5, ""),
                    results.get<std::string>(6, ""),
                    results.get<std::string>(7, ""),
                    results.get<std::string>(8, ""),
                    results.get<std::string>(9, "")});
            }
            return db_alerts;
        } catch (std::exception& e) {
            logger.Log(LogLevel::ERR, e.what(), "AlertDao", "GetAlerts");
            return std::nullopt;
        }
    }
    std::optional<bool> AlertDao::AddAlert(Alert alert) {
        logger.Log(LogLevel::INFO, "AlertDao", "AlertDao",
                   std::string("Alert message_id: ") + std::to_string(alert.message_id) +
                   ", identifier: " + alert.identifier +
                   ", originator_id: " + std::to_string(alert.originator_id) +
                   ", message_type: " + alert.message_type +
                   ", scope: " + alert.scope +
                   ", status: " + alert.status +
                   ", urgency: " + alert.urgency +
                   ", severity: " + alert.severity +
                   ", sent_time: " + alert.sent_time);
        try {
            nanodbc::connection connection(conn_str__);
            nanodbc::statement statement(connection);
            prepare(statement, NANODBC_TEXT("insert into " + db_alert_table__ +
                                            " (identifier, originator_id, message_type, scope, status," +
                                            " urgency, severity, sent_time, cap_xml)" +
                                            " values(?,?,?,?,?,?,?,?,?);"));
            nanodbc::string const identifier = NANODBC_TEXT(alert.identifier);
            statement.bind(0, identifier.c_str());
            const int originator_id = alert.originator_id;
            statement.bind(1, &originator_id);
            nanodbc::string const message_type = NANODBC_TEXT(alert.message_type);
            statement.bind(2, message_type.c_str());
            nanodbc::string const scope = NANODBC_TEXT(alert.scope);
            statement.bind(3, scope.c_str());
            nanodbc::string const status = NANODBC_TEXT(alert.status);
            statement.bind(4, status.c_str());
            nanodbc::string const urgency = NANODBC_TEXT(alert.urgency);
            statement.bind(5, urgency.c_str());
            nanodbc::string const severity = NANODBC_TEXT(alert.severity);
            statement.bind(6, severity.c_str());
            nanodbc::string const sent_time = NANODBC_TEXT(alert.sent_time);
            statement.bind(7, sent_time.c_str());
            nanodbc::string const cap_xml = NANODBC_TEXT(alert.cap_xml);
            statement.bind(8, cap_xml.c_str());
            // TODO(Vaniya): Verify the DB inserted successfully.
            execute(statement);

            nanodbc::result results;
            results = execute(connection, NANODBC_TEXT("SELECT LAST_INSERT_ID();"));
            results.next();
            int newId = results.get<int>(0, 0);
            logger.Log(LogLevel::DEBUG, "Has id: " + newId);
            if (results.next() && newId > 0) {
                alert.message_id = newId;
            }
        } catch (std::exception &e) {
            logger.Log(LogLevel:ERR, e.what(), "AlertDao", "AddAlert");
            return std::nullopt;
        }
        return true;
    }
}   // namespace cadg_rest