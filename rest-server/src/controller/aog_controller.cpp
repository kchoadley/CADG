//
// Created by shulce on 1/16/19.
//

#include <cpprest/uri_builder.h>
#include <cpprest/base_uri.h>
#include <iostream>
#include <string>
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
            std::vector<Aog> aogs;
            if (queries.count("name") > 0) {
                aogs = dao__.GetAogByName(queries["name"]);
            } else {
                aogs = dao__.GetAogs();
            }
            for (auto& aog : aogs) {
                response["aogs"][std::to_string(aog.id)] = aog.to_json();
            }
            message.reply(status_codes::OK, response);

        } catch (std::exception& e) {
            logger__.Log(LogLevel::ERR, e.what(), "AogController", "Handleget");
            message.reply(status_codes::InternalError, json::value::string(e.what()));
        }
    }

    void AogController::HandlePut(http_request message) {
        logger__.LogNetworkActivity(message, endpoint(), 2);

        message.reply(status_codes::NotImplemented);

    }

    void AogController::HandlePost(http_request message) {
        logger__.LogNetworkActivity(message, endpoint(), 2);

        message.reply(status_codes::NotImplemented);
    }

    void AogController::HandleDelete(http_request message) {
        logger__.LogNetworkActivity(message, endpoint(), 2);

        message.reply(status_codes::NotImplemented);
    }


} // end cadg_rest
