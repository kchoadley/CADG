/// Converts any syntactically correct SOAP CAP document into a CMAC XML document.
/**
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 *
 * @file    cmac_converter.cpp
 * @authors Ross Arcemont
 * @date    January, 2019
 */
#include <iostream>
#include <string>
#include <ctime>
#include "cmac_converter.hpp"
#include "../pugixml-1.9/src/pugixml.hpp"
#include "../../rest-server/src/model/cmac/cmac_alert.hpp"

void CMAC::convert(CADG_REST_SERVER_CMAC_ALERT_HPP::cmac::CMAC_alert alert_content, std::string cmac_filename) {
    // Obtaining the current date-time for later use.
    std::time_t time = std::time(0);
    std::tm* current_date_time = std::localtime(&time);
    //TODO: Ensure correctness
    std::string date_time_str = std::to_string((current_date_time->tm_year + 1900)) +
                                '-' + std::to_string((current_date_time->tm_mon + 1)) +
                                '-' + std::to_string(current_date_time->tm_mday) +
                                'T' + std::to_string(current_date_time->tm_hour) +
                                ':' + std::to_string(current_date_time->tm_min) +
                                ':' + std::to_string(current_date_time->tm_sec) + 'Z';

    // Pulling the SOAP CAP document into memory.
//    pugi::xml_document soap_doc;
//    pugi::xml_parse_result result = soap_doc.load_file(soap_filename.c_str());
//    pugi::xml_node cap_message = soap_doc.first_child().first_child().first_child();

    // Creating the CMAC document and declaring its root node.
    pugi::xml_document cmac_doc;
    pugi::xml_node declaration_node = cmac_doc.append_child(pugi::node_declaration);
    declaration_node.append_attribute("version") = "1.0";
    pugi::xml_node root_node = cmac_doc.append_child("CMAC_Alert_Attributes");
    root_node.append_attribute("xmlns") = "\"cmac:2.0\""; //TODO: Check value. Potentially temporary.

    //Creating the node structure and node content for the CMAC_Alert_Attributes block.
    //All node variable names match the corresponding CMAC structure as closely as possible.
    pugi::xml_node cmac_protocol_version = root_node.append_child("CMAC_protocol_version");
    cmac_protocol_version.text().set(alert_content.cmac_protocol_version.value()); //TODO: Determine how to get the protocol version based on either CAP message or other source.

    pugi::xml_node cmac_sending_gateway_id = root_node.append_child("CMAC_sending_gateway_id");
    cmac_sending_gateway_id.text().set(alert_content.cmac_sending_gateway_id.value()); //TODO: Determine how to get gateway IP or URI.

    pugi::xml_node cmac_message_number = root_node.append_child("CMAC_message_number");
    cmac_message_number.text().set(alert_content.cmac_message_number.value()); //TODO: Determining how to identify CMSP-initiated value, when applicable.

    if (alert_content.cmac_referenced_message_number) {
        pugi::xml_node cmac_referenced_message_number = root_node.append_child("CMAC_referenced_message_number");
        cmac_referenced_message_number.text().set(alert_content.cmac_referenced_message_number.value());
    }

    if (alert_content.cmac_referenced_message_cap_identifier) {
        pugi::xml_node cmac_referenced_message_cap_identifier = root_node.append_child("CMAC_referenced_message_cap_identifier");
        cmac_referenced_message_cap_identifier.text().set(alert_content.cmac_referenced_message_cap_identifier.value());
    }

    if (alert_content.cmac_special_handling) {
        pugi::xml_node cmac_special_handling = root_node.append_child("CMAC_special_handling");
        cmac_special_handling.text().set(alert_content.cmac_special_handling.value()); //TODO: Ensure correctness.
    }

    if (alert_content.cmac_sender) {
        pugi::xml_node cmac_sender = root_node.append_child("CMAC_sender");
        cmac_sender.text().set(alert_content.cmac_sender.value());
    }

    pugi::xml_node cmac_sent_date_time = root_node.append_child("CMAC_sent_date_time");
    cmac_sent_date_time.text().set(date_time_str.c_str());

    pugi::xml_node cmac_status = root_node.append_child("CMAC_status");
    cmac_status.text().set(alert_content.cmac_status.value());

    pugi::xml_node cmac_message_type = root_node.append_child("CMAC_message_type");
    cmac_message_type.text().set(alert_content.cmac_message_type.value());

    for (int i = 0; i < alert_content.cmac_response_code.size(); i++) {
        pugi::xml_node cmac_response_code = root_node.append_child("CMAC_response_code");
        cmac_response_code.text().set(alert_content.cmac_response_code.at(i).value());
    }

    for (int i = 0; i < alert_content.cmac_note.size(); i++) {
        pugi::xml_node cmac_note = root_node.append_child("CMAC_note");
        cmac_note.text().set(alert_content.cmac_note.at(i).value());
    }

    if (alert_content.cmac_cap_alert_uri) {
        pugi::xml_node cmac_cap_alert_uri = root_node.append_child("CMAC_cap_alert_uri");
        cmac_cap_alert_uri.text().set(alert_content.cmac_cap_alert_uri.value()); //TODO: Determine how to obtain from the gateway.
    }

    if (alert_content.cmac_cap_identifier) {
        pugi::xml_node cmac_cap_identifier = root_node.append_child("CMAC_cap_identifier");
        cmac_cap_identifier.text().set(alert_content.cmac_cap_identifier.value());
    }

    if (alert_content.cmac_cap_sent_date_time) {
        pugi::xml_node cmac_cap_sent_date_time = root_node.append_child("CMAC_cap_sent_date_time");
        cmac_cap_sent_date_time.text().set(alert_content.cmac_cap_sent_date_time.value());
    }

    //Creating the node structure and node content for the CMAC_alert_info block.
    //All node variable names match the corresponding CMAC structure as closely as possible.
    if (alert_content.cmac_alert_info) {
        pugi::xml_node cmac_alert_info = root_node.append_child("CMAC_alert_info");
        pugi::xml_node cmac_category = cmac_alert_info.append_child("CMAC_category");
        cmac_category.text().set(alert_content.cmac_alert_info.cmac_category.value());

        if (alert_content.cmac_alert_info.cmac_response_type) {
            pugi::xml_node cmac_response_type = cmac_alert_info.append_child("CMAC_response_type");
            cmac_response_type.text().set(alert_content.cmac_alert_info.cmac_response_type.value());
        }

        pugi::xml_node cmac_severity = cmac_alert_info.append_child("CMAC_severity");
        cmac_severity.text().set(alert_content.cmac_alert_info.cmac_severity.value());

        pugi::xml_node cmac_urgency = cmac_alert_info.append_child("CMAC_urgency");
        cmac_urgency.text().set(alert_content.cmac_alert_info.cmac_urgency.value());

        pugi::xml_node cmac_certainty = cmac_alert_info.append_child("CMAC_certainty");
        cmac_certainty.text().set(alert_content.cmac_alert_info.cmac_certainty.value());

        pugi::xml_node cmac_expires_date_time = cmac_alert_info.append_child("CMAC_expires_date_time");
        cmac_expires_date_time.text().set(alert_content.cmac_alert_info.cmac_expires_date_time.value());

        if (alert_content.cmac_alert_info.cmac_sender_name) {
            pugi::xml_node cmac_sender_name = cmac_alert_info.append_child("CMAC_sender_name");
            cmac_sender_name.text().set(alert_content.cmac_alert_info.cmac_sender_name.value());
        }
    }

    for (int i = 0; i < alert_content.cmac_alert_info.cmac_alert_area.size(); i++) {
        //Creating the node structure and node content for the CMAC_Alert_Area block.
        //All node variable names match the corresponding CMAC structure as closely as possible.
        pugi::xml_node cmac_alert_area = cmac_alert_info.append_child("CMAC_Alert_Area");
        pugi::xml_node cmac_area_description = cmac_alert_area.append_child("CMAC_area_description");
        cmac_area_description.text().set(alert_content.cmac_alert_info.cmac_alert_area.at(i).cmac_area_description.vlaue());

        for (int j = 0; j < alert_content.cmac_alert_info.cmac_alert_area.at(i).cmac_polygon.size(); j++) {
            pugi::xml_node cmac_polygon = cmac_alert_area.append_child("CMAC_polygon");
            cmac_polygon.text().set(alert_content.cmac_alert_info.cmac_alert_area.at(i).cmac_polygon.at(j).value());
        }

        for (int j = 0; j < alert_content.cmac_alert_info.cmac_alert_area.at(i).cmac_circle.size(); j++) {
            pugi::xml_node cmac_circle = cmac_alert_area.append_child("CMAC_circle");
            cmac_circle.text().set(alert_content.cmac_alert_info.cmac_alert_area.at(i).cmac_circle.at(j).value());
        }

        for (int j = 0; j < alert_content.cmac_alert_info.cmac_alert_area.at(i).cmac_cmas_geocode.size(); j++) {
            pugi::xml_node cmac_cmas_geocode = cmac_alert_area.append_child("CMAC_cmas_geocode");
            cmac_cmas_geocode.text().set(alert_content.cmac_alert_info.cmac_alert_area.at(i).cmac_cmas_geocode.at(j).value());
        }

        //TODO: Complete when CMAC object's geocode data is corrected
        //Creating geocode nodes and filling with content
        for (pugi::xml_node geocode = cap_message.child("info").child("area").first_child(); geocode ; geocode = geocode.next_sibling()) {
            std::string node_name = geocode.name();
            if(node_name.compare("geocode") == 0) {
                pugi::xml_node cmac_cap_geocode = cmac_alert_area.append_child("CMAC_cap_geocode");
                pugi::xml_node value_name = cmac_cap_geocode.append_child("valueName");
                pugi::xml_node value = cmac_cap_geocode.append_child("value");

                value_name.text().set(geocode.child("valueName").text().get());
                value.text().set(geocode.child("value").text().get());
            }
        }

        for (int j = 0; j < alert_content.cmac_alert_info.cmac_alert_area.at(i).cmac_gnis.size(); j++) {
            pugi::xml_node cmac_gnis = cmac_alert_area.append_child("CMAC_gnis");
            cmac_gnis.text().set(alert_content.cmac_alert_info.cmac_alert_area.at(i).cmac_gnis.at(j).value());
        }
    }

    for (int i = 0; i < alert_content.cmac_alert_info.cmac_alert_text.size(); i++) {
        //Creating the node structure and node content for the CMAC_Alert_Text block.
        //All node variable names match the corresponding CMAC structure as closely as possible.
        pugi::xml_node cmac_alert_text = cmac_alert_info.append_child("CMAC_Alert_Text");
        pugi::xml_node cmac_text_language = cmac_alert_text.append_child("CMAC_text_language");
        cmac_text_language.text().set(alert_content.cmac_alert_info.cmac_alert_text.at(i).cmac_language.value());

        pugi::xml_node cmac_short_text_alert_message_length = cmac_alert_text.append_child("CMAC_short_text_alert_message_length");
        cmac_short_text_alert_message_length.text().set(alert_content.cmac_alert_info.cmac_alert_text.at(i).cmac_short_text_alert_message_length.value()); //TODO: Determine value

        pugi::xml_node cmac_short_text_alert_message = cmac_alert_text.append_child("CMAC_short_text_alert_message");
        cmac_short_text_alert_message.text().set(alert_content.cmac_alert_info.cmac_alert_text.at(i).cmac_short_text_alert_message.value());

        pugi::xml_node cmac_long_text_alert_message_length = cmac_alert_text.append_child("CMAC_long_text_alert_message_length");
        cmac_long_text_alert_message_length.text().set(alert_content.cmac_alert_info.cmac_alert_text.at(i).cmac_long_text_alert_message_length.value());

        pugi::xml_node cmac_long_text_alert_message = cmac_alert_text.append_child("CMAC_long_text_alert_message");
        cmac_long_text_alert_message.text().set(alert_content.cmac_alert_info.cmac_alert_text.at(i).cmac_long_text_alert_message_length.value());
    }

    //Creating the node structure and node content for the CMAC_Digital_Signature block.
    //All node variable names match the corresponding CMAC structure as closely as possible.
    pugi::xml_node cmac_digital_signature = root_node.append_child("CMAC_Digital_Signature");
    cmac_digital_signature.text().set(alert_content.cmac_digital_signature.value());

    // Saving CMAC document.
    bool saved = cmac_doc.save_file(cmac_filename.c_str());
}

// int main() {
//    CMAC::convert("soap_message_test.xml", "test.xml");
// }