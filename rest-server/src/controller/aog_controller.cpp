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

        message.reply(status_codes::OK);
    }

    void AogController::HandlePut(http_request message) {
        logger__.LogNetworkActivity(message, endpoint(), 2);

        message.reply(status_codes::Accepted);

    }

    void AogController::HandlePost(http_request message) {
        logger__.LogNetworkActivity(message, endpoint(), 2);

        message.reply(status_codes::Created);
    }

    void AogController::HandleDelete(http_request message) {
        logger__.LogNetworkActivity(message, endpoint(), 2);

        message.reply(status_codes::Accepted);
    }


} // end cadg_rest
