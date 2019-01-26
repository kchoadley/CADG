/**
 *  Alert Originator Groups API Endpoint Controller
 *
 * Copyright 2019   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley, Shawn Hulce, Michael McCulley
 *
 * @file        aog_controller.cpp
 * @authors     Shawn Hulce
 * @date        January 2019
 */

#include <cpprest/uri_builder.h>
#include <cpprest/base_uri.h>
#include <iostream>
#include <string>
#include <vector>
#include "aog_controller.hpp"
#include "log_level.hpp"

using cadg_rest::LogLevel;

namespace cadg_rest {
    void AogController::InitHandlers() {
        listener__.support(methods::GET, std::bind(&AogController::HandleGet, this, std::placeholders::_1));
        listener__.support(methods::PUT, std::bind(&AogController::HandlePut, this, std::placeholders::_1));
        listener__.support(methods::POST, std::bind(&AogController::HandlePost, this, std::placeholders::_1));
        listener__.support(methods::DEL, std::bind(&AogController::HandleDelete, this, std::placeholders::_1));
    }

    void AogController::HandleGet(http_request message) {
        logger__.LogNetworkActivity(message, endpoint(), 2);
        try {
            auto response = json::value::object();
            response["aogs"] = json::value::object();
            auto queries = Queries(message.relative_uri().query());
            auto relative_path = message.relative_uri().to_string();
            std::optional<std::vector<Aog>> aogs;
            if (queries.count("name") > 0) {
                aogs = dao__.GetAogByName(queries["name"]);
            } else if (queries.count("agency") > 0) {
                    aogs = dao__.GetAogsByAgency(queries["agency"]);
            } else if (queries.count("id") > 0) {
                    aogs = dao__.GetAogById(std::stoi(queries["id"]));
            } else {
                    aogs = dao__.GetAogs();
            }
            if (aogs) {
                for (auto &aog : *aogs) {
                    response["aogs"][std::to_string(aog.id)] = aog.to_json();
                }
            } else {
                message.reply(status_codes::BadRequest, "No Data Found");
                return;
            }
            message.reply(status_codes::OK, response);
        } catch (std::exception& e) {
            logger__.Log(LogLevel::ERR, e.what(), "AogController", "Handleget");
            message.reply(status_codes::InternalError, json::value::string(e.what()));
        }
    }

    void AogController::HandlePut(http_request message) {
        logger__.LogNetworkActivity(message, endpoint(), 2);
        try {
            const json::value body_json = message.extract_json().get();
            if (body_json.has_field("id") && body_json.at("id").is_integer()) {
                if (auto aog_exists = dao__.GetAogById(body_json.at("id").as_integer())) {
                    Aog aog = aog_exists.value()[0];
                    logger__.Log(LogLevel::DEBUG, "Aog Found: " + std::to_string(aog.id) + " " +
                            aog.name + " " + aog.agency);
                    if (body_json.has_field("name") && body_json.at("name").is_string()) {
                        aog.name = body_json.at("name").as_string();
                    }
                    if (body_json.has_field("agency") && body_json.at("agency").is_string()) {
                        aog.agency = body_json.at("agency").as_string();
                    }
                    if (auto updated = dao__.UpdateAog(aog)) {
                        message.reply(status_codes::Accepted);
                        return;
                    }
                }
            }
            message.reply(status_codes::BadRequest);
        } catch (std::exception& e) {
            logger__.Log(LogLevel::ERR, e.what(), "AogController", "HandlePut");
            message.reply(status_codes::InternalError, json::value::string(e.what()));
        }
    }

    void AogController::HandlePost(http_request message) {
        logger__.LogNetworkActivity(message, endpoint(), 2);
        try {
            // parse body and extract user data
            const json::value body_json = message.extract_json().get();
            // validate user data
            // if valid add using dao
            auto aogs_json = body_json.as_object();
            if (auto valid_aog = Aog::from_json(body_json)) {
                dao__.AddAog(*valid_aog);
            } else {
                message.reply(status_codes::BadRequest);
                return;
            }
            // respond with successfully created (201)
            message.reply(status_codes::Created);
        } catch (std::exception&  e) {
            logger__.Log(LogLevel::WARN, e.what(), "AogController", "HandlePost");
            message.reply(status_codes::BadRequest, e.what());
        }
    }

    void AogController::HandleDelete(http_request message) {
        logger__.LogNetworkActivity(message, endpoint(), 2);
        try {
            const json::value body_json = message.extract_json().get();
            if (body_json.has_field("id") && body_json.at("id").is_integer()) {
                if (auto aog_exists = dao__.GetAogById(body_json.at("id").as_integer())) {
                    if (auto removed = dao__.DeleteAog(body_json.at("id").as_integer())) {
                        message.reply(status_codes::Accepted);
                        return;
                    }
                }
            }
            message.reply(status_codes::BadRequest);
        } catch (std::exception&  e) {
            logger__.Log(LogLevel::WARN, e.what(), "AogController", "HandleDelete");
            message.reply(status_codes::BadRequest, e.what());
        }
    }


}  // namespace cadg_rest
