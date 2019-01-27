/// A REST endpoint controller implementation class for alerts.
/**
 * AlertController implements the interface defined by Controller
 * and creates a REST endpoint for alerts.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 *
 * @file    alert_controller.cpp
 * @authors Vaniya Agrawal
 * @date    January, 2019
 */

#include <optional>
#include <cpprest/uri_builder.h>
#include <cpprest/base_uri.h>
#include <string>
#include "alert_controller.hpp"
#include "log_level.hpp"

using cadg_rest::AlertDaoInterface;

namespace cadg_rest {
    void AlertController::InitHandlers() {
        listener__.support(methods::GET, std::bind(&AlertController::HandleGet, this, std::placeholders::_1));
        listener__.support(methods::POST, std::bind(&AlertController::HandlePost, this, std::placeholders::_1));
        listener__.support(methods::PUT, std::bind(&AlertController::HandlePut, this, std::placeholders::_1));
        listener__.support(methods::DEL, std::bind(&AlertController::HandleDelete, this, std::placeholders::_1));
    }

    void AlertController::HandleGet(http_request message) {
        logger__.LogNetworkActivity(message, endpoint(), 2);
        try {
            auto response = json::value::object();
            response["alerts"] = json::value::object();
            auto queries = Queries(message.relative_uri().query());
            auto relative_path = message.relative_uri().to_string();
            if(auto alert_optional = dao__.GetAlerts()) {
                auto alerts = alert_optional.value();
                for(auto& alert : alerts) {
                    response["alerts"][std::to_string(alert.alert_id)] = alert.to_json();
                }
                message.reply(status_codes::OK, response);
            } else {
                message.reply(status_codes::InternalError, json::value::string("Unable to retrieve data"));
                return;
            }
        } catch (std::exception& e) {
            logger__.Log(LogLevel::WARN, e.what(), "AlertController", "HandleGet");
            message.reply(status_codes::InternalError, json::value::string(e.what()));
        }
    }
    void AlertController::HandlePost(http_request message) {
        logger__.LogNetworkActivity(message, endpoint(), 1);
        try {
            const json::value body_json = message.extract_json().get();
//            auto alert_json = body_json.as_object();
            if(auto alert = Alert::from_json(body_json)) {
                dao__.AddAlert(alert.value());
            } else {
                message.reply(status_codes::BadRequest);
                return;
            }
            message.reply(status_codes::Created);
        } catch (std::exception& e) {
            logger__.Log(LogLevel::WARN, e.what(), "AlertController", "HandlePost");
            message.reply(status_codes::BadRequest, e.what());
        }

    }
    void AlertController::HandlePut(http_request message) {

    }
    void AlertController::HandleDelete(http_request message) {

    }
}   // namespace cadg_rest