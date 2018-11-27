//
// Created by shulce on 11/27/18.
//
#include <cpprest/uri_builder.h>
#include <cpprest/base_uri.h>
#include <algorithm>
#include <iostream>
#include <string>
#include "soap_controller.hpp"
#include "log_level.hpp"
#include "../../gSoapFiles/CAP/ns1.nsmap"

namespace cadg_soap {
    void SoapController::InitHandlers() {
        listener__.support(methods::GET, std::bind(&SoapController::HandleGet, this, std::placeholders::_1));
        listener__.support(methods::PUT, std::bind(&SoapController::HandlePut, this, std::placeholders::_1));
        listener__.support(methods::POST, std::bind(&SoapController::HandlePost, this, std::placeholders::_1));
        listener__.support(methods::DEL, std::bind(&SoapController::HandleDelete, this, std::placeholders::_1));
    }

    void SoapController::HandlePost(http_request message) {
        logger__.LogNetworkActivity(message, endpoint(), 1);
        try {
            auto body = (soap) message.body();
            soap* soapmessage = &body;
            _ns1__alert alert;
            soap_read__ns1__alert(soapmessage, &alert);
            auto response = json::value::object();
            response["alert"] = json::value::object();
            if (&alert == NULL) {
                response["alert"][0] = 0;
            } else {
                response["alert"][0] = 1;
            }
            message.reply(status_codes::OK, response);

        } catch (std::exception& e) {
            message.reply(SOAP_FAULT);
        }
    }

    void SoapController::HandleGet(http_request message) {
        message.reply(status_codes::NotImplemented);
    }

    void SoapController::HandlePut(http_request message) {
        message.reply(status_codes::NotImplemented);
    }

    void SoapController::HandleDelete(http_request message) {
        message.reply(status_codes::NotImplemented);
    }

} //end cadg_soap
