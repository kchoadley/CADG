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
#include "../../gSoapFiles/IPAWS/soapStub.h"
#include "../../gSoapFiles/IPAWS/CAPSoapHttp.nsmap"
#include "../../services/log_level.hpp"

using cadg_rest::LogLevel;

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
            // Should generate soap context that can read input and create alert. Not sure how
//            struct soap ctx = *soap_new1(SOAP_C_UTFSTRING | SOAP_XML_IGNORENS | SOAP_XML_TREE);
            struct soap ctx = *soap_new2(SOAP_XML_STRICT, SOAP_XML_INDENT);
//            struct soap ctx = *soap_new();
//            _ns5__alert alertMessage;
            _ns2__postCAPRequestTypeDef incomingRequest;
            //incomingRequest.ns5__alert = &alertMessage;
            auto body = message.extract_string().get();
            //soap_envelope_begin_in()
//            logger__.Log(LogLevel::DEBUG, "Message Received: " + body, "SoapController", "HandlePost");
            std::stringstream str_stream;
//            std::stringstream soap_out;
            str_stream.str(body);  // passes message to into the string stream
            ctx.is = &str_stream;  // sets the instream of the soap ctx  object to the string input
//            ctx.os = &soap_out;  // sets the outstream of the soap ctx context
            // should read the soap context and output the details to the alertMessage object
            if (soap_read__ns2__postCAPRequestTypeDef(&ctx, &incomingRequest)) {
                if (incomingRequest.ns5__alert)
                    logger__.Log(LogLevel::DEBUG, "Sender: " + incomingRequest.ns5__alert->sender, "SoapController", "HandlePost");
                else
                    logger__.Log(LogLevel::DEBUG, "No alert.", "SoapController", "HandlePost");
            } else {
                soap_response(&ctx, SOAP_PROHIBITED);
            }
//            ctx.is = NULL;
//            auto soap_resp = soap_out.str();
//            logger__.Log(LogLevel::DEBUG, alertMessage.sender, "SoapController", "HandlePost");
            message.reply(status_codes::OK, "Reponse...");
        } catch (std::exception& e) {
            message.reply(status_codes::BadRequest);
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
