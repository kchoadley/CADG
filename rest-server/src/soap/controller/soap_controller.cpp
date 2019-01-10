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
#include "../../gSoapFiles/CAP/cadg_soapH.hpp"
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
            struct _ns1__alert alertMessage;
            std::string bodyContent = "";
            //Should generate soap context that can read input and create alert. Not sure how
            soap* ctx = soap_new2(SOAP_XML_STRICT, SOAP_XML_INDENT);
            auto body = message.extract_string().get();
            std::istringstream strStream;

            strStream.str(body);

            ctx->is = &strStream;

            soap_read__ns1__alert(ctx, &alertMessage);

            std::cout << alertMessage.identifier << std::endl;
            message.reply(status_codes::OK);

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
