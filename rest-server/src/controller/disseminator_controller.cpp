/// A REST endpoint controller implementation class for disseminators.
/**
 * DisseminatorController implements the interface defined by Controller.
 * This provides an example of how to use and inject a Data Access Object
 * as well as passing a logger to the base Controller.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 *
 * @file        disseminator_controller.hpp
 * @authors     Kristofer Hoadley
 * @date        January, 2019
 */
#include <optional>
#include <cpprest/uri_builder.h>
#include <cpprest/base_uri.h>
#include <string>
#include <vector>
#include "disseminator_controller.hpp"
#include "log_level.hpp"
using cadg_rest::DisseminatorDaoInterface;

namespace cadg_rest {
void DisseminatorController::InitHandlers() {
    listener__.support(methods::GET, std::bind(&DisseminatorController::HandleGet, this, std::placeholders::_1));
    listener__.support(methods::PUT, std::bind(&DisseminatorController::HandlePut, this, std::placeholders::_1));
    listener__.support(methods::POST, std::bind(&DisseminatorController::HandlePost, this, std::placeholders::_1));
    listener__.support(methods::DEL, std::bind(&DisseminatorController::HandleDelete, this, std::placeholders::_1));
}
void DisseminatorController::HandleGet(http_request message) {
    logger__.LogNetworkActivity(message, endpoint(), 2);
    try {
        auto response = json::value::object();
        auto queries = Queries(message.relative_uri().query());
        auto relative_path = message.relative_uri().to_string();
        logger__.Log(LogLevel::INFO, relative_path);

        if (relative_path.length() > 1) {  // There is a relative path
            if (relative_path.at(1) != '?') {  // It is not a query
                std::vector<std::string> path_segments = PathSegments(relative_path);
                if (path_segments[0].find_first_not_of("0123456789") == std::string::npos) {  // It is a disseminator ID
                    int id = std::stoi(path_segments[0]);
                    if (auto disseminator_response = dao__.GetDisseminatorByID(id)) {
                        auto disseminator = disseminator_response.value();
                        logger__.Log(LogLevel::DEBUG, "Name of found disseminator: " + disseminator.name);
                        if (disseminator.id > 0) {
                            response["disseminator"] = disseminator.to_json();
                            message.reply(status_codes::OK, response);
                        } else {
                            message.reply(status_codes::NotFound);
                        }
                    }
                } else {  // first path section must be a id to be valid
                    message.reply(status_codes::BadRequest, json::value::string("Bad Request"));
                }
            } else {  // Query string present
                message.reply(status_codes::NotImplemented,
                        json::value::string("Queries on Disseminators not implemented yet."));
            }
        } else if (auto disseminator_optional = dao__.GetDisseminators()) {
            response["disseminators"] = json::value::object();
            auto disseminators = disseminator_optional.value();
            for (auto& disseminator : disseminators) {
                response["disseminators"][std::to_string(disseminator.id)] = disseminator.to_json();
            }
            message.reply(status_codes::OK, response);
        } else {
            message.reply(status_codes::BadRequest, json::value::string("Bad Request"));
        }
    } catch (std::exception&  e) {
        logger__.Log(LogLevel::WARN, e.what(), "DisseminatorController", "HandleGet");
        // TODO(Kris): Remove error return e.what, returned for testing purposes only
        message.reply(status_codes::InternalError, json::value::string(e.what()));
    }
}
void DisseminatorController::HandlePut(http_request message) {
    logger__.LogNetworkActivity(message, endpoint(), 1);
    // TODO(Kris): Implement
    message.reply(status_codes::NotImplemented, json::value::string("Put Disseminators Not Implemented."));
    
}
void DisseminatorController::HandlePost(http_request message) {
    logger__.LogNetworkActivity(message, endpoint(), 1);
    try {
        const json::value body_json = message.extract_json().get();
        json::value disseminator_json = body_json.at("disseminator");
        if (auto disseminator_optional = Disseminator::from_json(disseminator_json)) {
            Disseminator disseminator = disseminator_optional.value();
            if (auto success_optional = dao__.AddDisseminator(disseminator)) {
                message.reply(status_codes::Created);
            } else {
                message.reply(status_codes::InternalError, json::value::string("Unable to post data"));
            }
        } else {
            message.reply(status_codes::BadRequest, json::value::string("Bad Request"));
        }
    } catch (std::exception&  e) {  // for testing purposes
        logger__.Log(LogLevel::WARN, e.what(), "DisseminatorController", "HandlePost");
        message.reply(status_codes::InternalError, json::value::string("Internal Error"));
    }
}
void DisseminatorController::HandleDelete(http_request message) {
    logger__.LogNetworkActivity(message, endpoint(), 1);
    // TODO(Kris): Implement
    message.reply(status_codes::NotImplemented, json::value::string("Delete Disseminators Not Implemented."));
}
}  // namespace cadg_rest