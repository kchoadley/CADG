/// Defines a model that represents an alert message.
/**
 * Contains an alert data structure for moving alert data to and
 * from a data store and a REST endpoint.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 *
 * @file    alert.hpp
 * @authors Vaniya Agrawal
 * @date    January, 2019
 */

#ifndef ALERT_H
#define ALERT_H

#include <optional>
#include <string>
#include <cpprest/json.h>
//#include "boost/date_time/gregorian/gregorian_types.hpp"
//#include "boost/date_time/posix_time/posix_time_types.hpp"

namespace cadg_rest {
    /// An alert struct.
    /**
     * An alert struct that contains the most important
     * information of the alert.
     */
    struct Alert {
        int message_id;
        std::string identifier;
        int originator_id;
        std::string message_type;
        std::string scope;
        std::string status;
        std::string urgency;
        std::string severity;
//        boost::gregorian::date sent_date;
//        boost::posix_time::ptime sent_time;
        std::string cap_xml;

        /// Convert Alert struct to JSON format.
        /**
         * Converts an struct to a json object.
         * @return The JSON representation of an alert.
         */
        web::json::value to_json() {
            auto alert_json = web::json::value::object();
            alert_json["message_id"] = web::json::value::number(message_id);
            alert_json["identifier"] = web::json::value::string(identifier);
            alert_json["originator_id"] = web::json::value::number(originator_id);
            alert_json["message_type"] = web::json::value::string(message_type);
            alert_json["scope"] = web::json::value::string(scope);
            alert_json["status"] = web::json::value::string(status);
            alert_json["urgency"] = web::json::value::string(urgency);
            alert_json["severity"] = web::json::value::string(severity);

            //  TODO: Vaniya
            //  utilize boost library to convert date/time to json

            alert_json["cap_xml"] = web::json::value::string(cap_xml);
            return alert_json;
        }

        /// Create an Alert struct from a json value.
        /**
         * Creates an Alert struct from a json value. If the JSON value does not pass
         * validation, a nullopt will be returned.
         *
         * @param alert_json    The json value representing the alert.
         * @return              The alert in Alert format, or a nullopt.
         */
        std::optional<Alert> from_json(web::json::value alert_json) {
            if( alert_json.has_field("message_id")      && alert_json["message_id"].is_integer() &&
                alert_json.has_field("identifier")      && alert_json["identifier"].is_string() &&
                alert_json.has_field("originator_id")   && alert_json["originator_id"].is_integer() &&
                alert_json.has_field("message_type")    && alert_json["message_type"].is_string() &&
                alert_json.has_field("scope")           && alert_json["scope"].is_string() &&
                alert_json.has_field("status")          && alert_json["status"].is_string() &&
                alert_json.has_field("urgency")         && alert_json["urgency"].is_string() &&
                alert_json.has_field("severity")        && alert_json["severity"].is_string() &&
//              alert_json.has_field("sent_date")       && alert_json["sent_date"].is_string() &&
//              alert_json.has_field("sent_time")       && alert_json["sent_time"].is_string() &&
                alert_json.has_field("cap_xml")         && alert_json["cap_xml"].is_string()) {

                Alert alert;
                alert.message_id = alert_json["message_id"].as_integer();
                alert.identifier = alert_json["alert_identifier"].as_string();
                alert.originator_id = alert_json["originator_id"].as_integer();
                alert.message_type = alert_json["message_type"].as_string();
                alert.scope = alert_json["scope"].as_string();
                alert.status = alert_json["status"].as_string();
                alert.urgency = alert_json["urgency"].as_string();
                alert.severity = alert_json["severity"].as_string();
//                alert.sent_date = alert_json["sent_date"].as_string();
//                alert.sent_time = alert_json["sent_time"].as_string();
                alert.cap_xml = alert_json["cap_xml"].as_string();

                return alert;
            } else {
                return std::nullopt;
            }
        }
    };
    /// Compares two alerts.
    /**
     * Returns whether or not two alerts match on all fields (excluding the CAP XML).
     * @param a The first alert.
     * @param b The second alert.
     * @return  True if the alerts match on every field (exc. CAP XML).
     */
    inline bool operator == (const Alert &a, const Alert &b) {
        return  a.message_id == b.message_id &&
                a.identifier == b.identifier &&
                a.originator_id == b.originator_id &&
                a.message_type == b.message_type &&
                a.scope == b.scope &&
                a.status == b.status &&
                a.urgency == b.urgency &&
                a.severity == b.severity &&
//                a.sent_date == b.sent_date &&
//                a.sent_time == b.sent_time
    }
}
#endif //CADG_REST_SERVER_ALERT_HPP
