/// A REST endpoint controller implementation class for admins.
/**
 * AdminController implements the interface defined by Controller.
 * This provides an example of how to use and inject a Data Access Object
 * as well as passing a logger to the base Controller.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 *
 * @file        admin_controller.hpp
 * @authors     Kristofer Hoadley
 * @date        January, 2019
 */
#include <optional>
#include <cpprest/uri_builder.h>
#include <cpprest/base_uri.h>
#include <string>
#include "admin_controller.hpp"
#include "log_level.hpp"
using cadg_rest::AdminDaoInterface;

namespace cadg_rest {
void AdminController::InitHandlers() {
    listener__.support(methods::GET, std::bind(&AdminController::HandleGet, this, std::placeholders::_1));
    listener__.support(methods::PUT, std::bind(&AdminController::HandlePut, this, std::placeholders::_1));
    listener__.support(methods::POST, std::bind(&AdminController::HandlePost, this, std::placeholders::_1));
    listener__.support(methods::DEL, std::bind(&AdminController::HandleDelete, this, std::placeholders::_1));
}
void AdminController::HandleGet(http_request message) {
    logger__.LogNetworkActivity(message, endpoint(), 2);
    try {
        auto response = json::value::object();
        response["admins"] = json::value::object();
        auto queries = Queries(message.relative_uri().query());
        auto relative_path = message.relative_uri().to_string();
        if (auto admin_optional = dao__.GetAdmins()) {
            auto admins = admin_optional.value();
            for (auto& admin : admins)
                response["admins"][std::to_string(admin.id)] = admin.to_json();
            message.reply(status_codes::OK, response);
        } else {
            message.reply(status_codes::InternalError, json::value::string("Unable to retrieve data"));
            return;
        }
    } catch (std::exception&  e) {
        logger__.Log(LogLevel::WARN, e.what(), "AdminController", "HandleGet");
        // TODO(Kris): Remove error return e.what, returned for testing purposes only
        message.reply(status_codes::InternalError, json::value::string(e.what()));
    }
}
void AdminController::HandlePut(http_request message) {
    // TODO(Kris): Implement
}
void AdminController::HandlePost(http_request message) {
    // TODO(Kris): Implement
}
void AdminController::HandleDelete(http_request message) {
    // TODO(Kris): Implement
}
bool AdminController::GetAdminByID(json::value& response, const std::string& path) {
    // TODO(Kris): Implement
    return false;
}
bool AdminController::GetAdminsByUsername(json::value& response, const std::string& username) {
    // TODO(Kris): Implement
    return false;
}
std::string AdminController::ParseAdminID(const std::string& path) {
    // TODO(Kris): Implement
    return std::string();
}
}  // namespace cadg_rest
