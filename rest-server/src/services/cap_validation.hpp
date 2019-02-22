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
#include <logger.hpp>
#include <logger_interface.hpp>
#include "log_level.hpp"
#include "../gSoapFiles/CAP/soapH.h"
#include <time.h>
#include <regex.h>

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

    static void string_to_vector(std::string s, std::string delimiter, std::vector<std::string> &elems) {
        size_t pos = 0;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            if (s.substr(0, pos) != "" )
                elems.push_back(s.substr(0, pos));
            s.erase(0, pos + delimiter.length());
        }
        if (s != "") {
            elems.push_back(s);
        }
    }

    static std::vector<std::string> parse_double_quoted_then_spaces(std::string s) {
        std::vector<std::string> elems;
        std::string delimiter = "\"";
        size_t pos = 0;
        int start_pos = 0;
        bool in_quote = false;
        while ((pos = s.find(delimiter, start_pos)) != std::string::npos) {
            if (!in_quote) {
                string_to_vector(s.substr(0, pos), " ", elems);
                s.erase(0, pos);
                start_pos = delimiter.length();
            } else {
                if (s.substr(start_pos, pos - delimiter.length()) != "") {
                    elems.push_back(s.substr(start_pos, pos - delimiter.length()));
                }
                s.erase(0, pos + delimiter.length());
                start_pos = 0;
            }
            in_quote = !in_quote;
        }
        string_to_vector(s, " ", elems);
        return elems;
    }

    static bool validate_addresses(std::string addresses) {
        // TODO(All): Are these addresses URLs?
        return true;
    }

    static bool validate_references(std::string references) {
        std::vector<std::string> refs = parse_double_quoted_then_spaces(references);
        for (auto ref = refs.begin(); ref != refs.end(); ++ref) {
            std::vector<std::string> ref_ids;
            string_to_vector(*ref, ",", ref_ids);
            if(ref_ids.size() != 3)
                return false;
        }
        return true;
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
            if (alert.restriction && *alert.restriction != "") {
                logger.Log(cadg_rest::LogLevel::DEBUG, "Restriction: " + *alert.restriction, "cap_validation", "validate_soap_alert");
            } else if (alert.scope == _ns2__alert_scope__Restricted) {
                logger.Log(cadg_rest::LogLevel::DEBUG, "No restriction provided with restricted scope.",
                           "cap_validation", "validate_soap_alert");
                // TODO(All): Decide if this required if scope is restricted.
                return false;
            }

            if (alert.addresses && *alert.addresses != "") {
                logger.Log(cadg_rest::LogLevel::DEBUG, "Addresses: " + *alert.addresses, "cap_validation", "validate_soap_alert");
                if (!validate_addresses(*alert.addresses)) {
                    logger.Log(cadg_rest::LogLevel::DEBUG, "Invalid format for addresses.", "cap_validation", "validate_soap_alert");
                    return false;
                }
            } else if (alert.scope == _ns2__alert_scope__Private) {
                logger.Log(cadg_rest::LogLevel::DEBUG, "No addresses provided with private scope.", "cap_validation", "validate_soap_alert");
                return false;
            }
            // Validate format of optional fields.
            if (alert.references && *alert.references != "") {
                logger.Log(cadg_rest::LogLevel::DEBUG, "References string: " + *alert.references, "cap_validation", "validate_soap_alert");
                if (!validate_references(*alert.references)){
                    logger.Log(cadg_rest::LogLevel::DEBUG, "Invalid reference format.", "cap_validation", "validate_soap_alert");
                    return false;
                }
            }
            return true;
        } catch (...) {
            return false;
        }
    };
}
#endif //CAP_VALIDATION_H