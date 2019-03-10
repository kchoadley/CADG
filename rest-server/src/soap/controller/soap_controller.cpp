// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/// Controller for receiving SOAP CAP Alert HTTP requests.
/**
 * This class receives SOAP CAP Alert HTTP requests.
 *
 * @file        soap_controller.cpp
 * @authors     Shawn Hulce, Michael McCulley
 * @date        March, 2019
 */
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
            // Parse SOAP XML from request body into a pugixml document.
            auto body = message.extract_string().get();
            pugi::xml_document soap_doc;
            pugi::xml_parse_result result = soap_doc.load_string(body.c_str());
            if (!result)  {
                logger__.Log(LogLevel::DEBUG, "pugixml failed to parse request body.", "SoapController", "HandlePost");
                message.reply(status_codes::UnprocessableEntity, "Invalid CAP message.");
            }

            // Search the SOAP envelope attributes for the alert namespace
            // and set variable for the namespace prefix.
            std::string alert_ns_prefix;
            const std::string ALERT_NS = "urn:oasis:names:tc:emergency:cap:1.2";
            for (pugi::xml_attribute attr: soap_doc.first_child().attributes()) {
                std::string attr_name = attr.name();
                if (attr_name.size() > 6 && attr_name.substr(0,6) == "xmlns:" && attr.value() == ALERT_NS) {
                    alert_ns_prefix = attr_name.substr(6,attr_name.length()-6) + ":";
                    break;
                }
            }

            // A functor with a predicate to test if a pugixml node has a given name.
            // Used to find the alert root node below.
            struct has_name {
                has_name(const std::string& node_name) : node_name_(node_name) {};
                std::string node_name_;
                bool operator()(pugi::xml_node node) const {
                    return (node.name() == node_name_);
                }
            };

            // Another pugixml document to hold only the CAP XML from the SOAP XML.
            // This XML be read into the gSoap _ns2__alert.
            pugi::xml_document cap_doc;
            pugi::xml_node dec_node = cap_doc.append_child(pugi::node_declaration);
            dec_node.append_attribute("version") = "1.0";
            pugi::xml_node cap_node = soap_doc.find_node(has_name(alert_ns_prefix + "alert"));
            cap_doc.append_copy(cap_node);

            // A pugixml tree walker to traverse the XML and scrub the node names of
            // the namespace prefix. Additionally, the walker appends the namespace
            // as an xmlns attribute to the root node of the namespace.
            struct ns_walker: pugi::xml_tree_walker {
                std::string ns_prefix;
                std::string ns_value;
                std::string ns_node_name;
                virtual bool for_each(pugi::xml_node& node) {
                    std::string name = node.name();
                    if (name.size() > ns_prefix.size() && name.substr(0,ns_prefix.size()) == ns_prefix) {
                        node.set_name(name.substr(ns_prefix.size(), name.size() - ns_prefix.size()).c_str());
                        if (node.name() == ns_node_name) {
                            pugi::xml_attribute attr = node.append_attribute("xmlns");
                            attr.set_value(ns_value.c_str());
                        }
                    }
                    return true;
                }
            };

            // Traverse the CAP XML and update the namespace formatting as
            // necessary for gSoap _ns2__alert objects.
            ns_walker walker;
            walker.ns_prefix = alert_ns_prefix;
            walker.ns_value = ALERT_NS;
            walker.ns_node_name = "alert";
            cap_doc.traverse(walker);
            // Output CAP XML into a stringstream.
            std::stringstream cap_xml_stream;
            cap_doc.save(cap_xml_stream);
            logger__.Log(LogLevel::DEBUG, "CAP XML:\n" + cap_xml_stream.str(), "SoapController", "HandlePost");

            // Parse CAP XMLd into gSoap objects.
            // Should generate soap context that can read input and create alert. Not sure how
            struct soap ctx = *soap_new2(SOAP_XML_STRICT, SOAP_XML_INDENT);
            ctx.is = &cap_xml_stream;  // sets the instream of the soap ctx  object to the string input stream
            // should read the soap context and output the details to the alertMessage object
            _ns2__alert alertMessage;
            soap_read__ns2__alert(&ctx, &alertMessage);
            // Validate the alert per CAP for IPAWS specifications.
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
