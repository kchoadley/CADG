// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/// Functions for validating CAP Alert Messages.
/**
 * This class contains functions for validating CAP Alert Messages.
 *
 * @file        cap_validation.hpp
 * @authors     Michael McCulley
 * @date        February, 2019
 */

#ifndef CAP_VALIDATION_H
#define CAP_VALIDATION_H
#include <optional>
#include <logger.hpp>
#include <logger_interface.hpp>
#include "log_level.hpp"
#include "../gSoapFiles/CAP/soapH.h"
#include <time.h>

namespace cap_validation {
    static std::string time_t_to_xml_dt_string(const time_t &time) {
        struct tm* time_info = localtime(&time);
        char date_buffer [27];
        strftime (date_buffer, 27,"%FT%T%z", time_info);
        std::string date_str = date_buffer;
        if (date_str.size() > 2)
            date_str = date_str.substr(0, date_str.size() - 2) + ":" + date_str.substr(date_str.size() - 2);
        return date_str;
    }

    static bool validate_soap_alert(const _ns2__alert &alert) {
        try {
            auto &logger(cadg_rest::Logger::Instance());
            logger.Log(cadg_rest::LogLevel::DEBUG, "Validating required CAP fields...", "cap_validation", "validate_soap_alert");
            // Validate required fields.
            logger.Log(cadg_rest::LogLevel::DEBUG, "Identifier: " + alert.identifier, "cap_validation", "validate_soap_alert");
            if (alert.identifier == "") {
                // TODO(All): Validate uniqueness against DAO.
                return false;
            }
            logger.Log(cadg_rest::LogLevel::DEBUG, "Sender: " + alert.sender, "cap_validation", "validate_soap_alert");
            if (alert.sender == "") {
                // TODO(All): Validate valid sender against DAO.
                return false;
            }
            logger.Log(cadg_rest::LogLevel::DEBUG, "Sent: " + std::to_string(alert.sent), "cap_validation", "validate_soap_alert");
            if (alert.sent <= 0) {
                // TODO(All): Constrain dates logically?
                return false;
            }
            logger.Log(cadg_rest::LogLevel::DEBUG, "Status: " + std::to_string(alert.status), "cap_validation", "validate_soap_alert");
            if (alert.status < 0) {
                return false;
            }
            logger.Log(cadg_rest::LogLevel::DEBUG, "Message Type: " + std::to_string(alert.msgType), "cap_validation", "validate_soap_alert");
            if (alert.msgType < 0) {
                return false;
            }
            logger.Log(cadg_rest::LogLevel::DEBUG, "Scope: " + std::to_string(alert.scope), "cap_validation", "validate_soap_alert");
            if (alert.scope < 0) {
                return false;
            }
            logger.Log(cadg_rest::LogLevel::DEBUG, "Code vector size: " + std::to_string(alert.code.size()), "cap_validation", "validate_soap_alert");
            if (alert.code.size() == 0) {
                // TODO(All): Is this really required? It is required per the IPAWS profile but omited in examples.
                return false;
            }
            bool ipaws_profile_code_found = false;
            for (int i = 0; i < alert.code.size(); ++i) {
                logger.Log(cadg_rest::LogLevel::DEBUG, "Code[" + std::to_string(i+1) + "]: " + alert.code[i], "cap_validation", "validate_soap_alert");
                if (alert.code[i].find("IPAWSv1.0") != std::string::npos) {
                    ipaws_profile_code_found = true;
                    break;
                }
            }
            if (!ipaws_profile_code_found)
                return false;
            // Validate conditional fields.

            // Validate format of all fields.
            return true;
        } catch (...) {
            return false;
        }
    };
}
#endif //CAP_VALIDATION_H