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
#include <ctime>
#include <cpprest/json.h>

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
        std::time_t sent_time;
        std::string cap_xml;

        web::json::value to_json() {}

        std::optional<Alert> from_json(web::json::value alert_json) {}
    };
    inline bool operator == (const Alert &a, const Alert &b) {}
}
#endif //CADG_REST_SERVER_ALERT_HPP
