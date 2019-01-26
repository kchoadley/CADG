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

    }
    void AlertController::HandlePost(http_request message) {

    }
    void AlertController::HandlePut(http_request message) {

    }
    void AlertController::HandleDelete(http_request message) {

    }
}   // namespace cadg_rest