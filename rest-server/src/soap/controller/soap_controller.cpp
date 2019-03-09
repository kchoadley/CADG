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
#include "../../gSoapFiles/CAP/soapH.h"
#include "../../gSoapFiles/CAP/ns2.nsmap"
#include "cap_validation.hpp"
#include "../../../../soap/pugixml-1.9/src/pugixml.hpp"
#include "../../../../soap/pugixml-1.9/src/pugixml.cpp"

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
            _ns2__alert alertMessage;
            // Should generate soap context that can read input and create alert. Not sure how
            struct soap ctx = *soap_new2(SOAP_XML_STRICT, SOAP_XML_INDENT);
            auto body = message.extract_string().get();
            pugi::xml_document soap_doc;
            pugi::xml_parse_result result = soap_doc.load_string(body.c_str());
            pugi::xml_node cap_message = soap_doc.first_child().first_child().first_child();
            logger__.Log(LogLevel::DEBUG, "CAP node value: " + *cap_message.value(), "SoapController", "HandlePost");

            //pugi::xml_document cap_doc;
            //pugi::xml_node declaration_node = cap_doc.append_child(pugi::node_declaration);
            //declaration_node.append_attribute("version") = "1.0";
            //pugi::xml_node root_node = cap_doc.append_child(cap_message.value());
            //std::stringstream pugi_str_stream;
            //cap_doc.save(pugi_str_stream);

            logger__.Log(LogLevel::DEBUG, "SOAP Received: " + body, "SoapController", "HandlePost");
            std::stringstream str_stream;
            str_stream.str(cap_message.value());  // passes message body to into the string stream
            ctx.is = &str_stream;  // sets the instream of the soap ctx  object to the string input stream
            // should read the soap context and output the details to the alertMessage object
            soap_read__ns2__alert(&ctx, &alertMessage);
            bool alert_is_valid = cap_validation::validate_soap_alert(alertMessage);
            if (!alert_is_valid) {
                logger__.Log(LogLevel::DEBUG, "Soap alert invalid.", "SoapController", "HandlePost");
                message.reply(status_codes::UnprocessableEntity, "Invalid CAP message.");
            }
            else {
                logger__.Log(LogLevel::DEBUG, "Soap alert valid.", "SoapController", "HandlePost");
                message.reply(status_codes::OK, "Got it");
            }
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
