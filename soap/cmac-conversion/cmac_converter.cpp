// Created by Ross on 1/18/2019.
// Currently only reads in an existing SOAP file
// into memory and displays the status node to prove read functionality.

#include <iostream>
#include <string>
#include <ctime>
#include "cmac_converter.hpp"
#include "../pugixml-1.9/src/pugixml.hpp"
#include "../pugixml-1.9/src/pugixml.cpp"

void CMAC::convert(std::string soap_filename, std::string cmac_filename) {
    //Obtaining the current date-time for later use.
    std::time_t time = std::time(0);
    std::tm* current_date_time = std::localtime(&time);
    std::string date_time_str = std::to_string((current_date_time->tm_year + 1900)) + '-' + std::to_string((current_date_time->tm_mon + 1)) + '-' + std::to_string(current_date_time->tm_mday) + 'T' + std::to_string(current_date_time->tm_hour) + ':' + std::to_string(current_date_time->tm_min) + ':' + std::to_string(current_date_time->tm_sec) + 'Z';

    //Pulling the SOAP document into memory.
    pugi::xml_document soap_doc;
    pugi::xml_parse_result result = soap_doc.load_file(soap_filename.c_str());
    pugi::xml_node cap_message = soap_doc.first_child().first_child().first_child();

    //Creating the CMAC document and declaring its root node.
    pugi::xml_document cmac_doc;
    auto declaration_node = cmac_doc.append_child(pugi::node_declaration);
    declaration_node.append_attribute("version") = "1.0";
    auto root_node = cmac_doc.append_child("CMAC_Alert_Attributes");

    //Creating the node structure for the entire CMAC document.
    //All node variable names match the corresponding CMAC
    //structure as closely as possible.
    auto cmac_protocol_version = root_node.append_child("CMAC_protocol_version");
    auto cmac_sending_gateway_id = root_node.append_child("CMAC_sending_gateway_id");
    auto cmac_message_number = root_node.append_child("CMAC_message_number");
    auto cmac_referenced_message_cap_identifier = root_node.append_child("CMAC_referenced_message_cap_identifier");
    auto cmac_special_handling = root_node.append_child("CMAC_special_handling");
    auto cmac_sender = root_node.append_child("CMAC_sender");
    auto cmac_sent_date_time = root_node.append_child("CMAC_sent_date_time");
    auto cmac_status = root_node.append_child("CMAC_status");
    auto cmac_message_type = root_node.append_child("CMAC_message_type");
    auto cmac_response_code = root_node.append_child("CMAC_response_code");
    auto cmac_note = root_node.append_child("CMAC_note");
    auto cmac_cap_alert_uri = root_node.append_child("CMAC_cap_alert_uri");
    auto cmac_cap_identifier = root_node.append_child("CMAC_cap_identifier");
    auto cmac_cap_sent_date_time = root_node.append_child("CMAC_cap_sent_date_time");
    auto cmac_alert_info = root_node.append_child("CMAC_alert_info");

    auto cmac_category = cmac_alert_info.append_child("CMAC_category");
    auto cmac_event_code = cmac_alert_info.append_child("CMAC_event_code");
    auto cmac_response_type = cmac_alert_info.append_child("CMAC_response_type");
    auto cmac_severity = cmac_alert_info.append_child("CMAC_severity");
    auto cmac_urgency = cmac_alert_info.append_child("CMAC_urgency");
    auto cmac_certainty = cmac_alert_info.append_child("CMAC_certainty");
    auto cmac_expires_date_time = cmac_alert_info.append_child("CMAC_expires_date_time");
    auto cmac_sender_name = cmac_alert_info.append_child("CMAC_sender_name");
    auto cmac_text_language = cmac_alert_info.append_child("CMAC_text_language");
    auto cmac_text_alert_message_length = cmac_alert_info.append_child("CMAC_text_alert_message_length");
    auto cmac_text_alert_message = cmac_alert_info.append_child("CMAC_text_alert_message");
    auto cmac_alert_area = cmac_alert_info.append_child("CMAC_Alert_Area");

    auto cmac_area_description = cmac_alert_area.append_child("CMAC_area_description");
    auto cmac_cmas_geocode = cmac_alert_area.append_child("CMAC_cmas_geocode");
    auto cmac_cap_geocode = cmac_alert_area.append_child("CMAC_cap_geocode");

    //TODO: Make this loop through all CAP message geocode points and add them individually
    auto value_name = cmac_cap_geocode.append_child("valueName");
    auto value = cmac_cap_geocode.append_child("value");

    auto cmac_digital_signature = root_node.append_child("CMAC_Digital_Signature");

    auto signature = cmac_digital_signature.append_child("Signature");

    auto signed_info = signature.append_child("SignedInfo");
    auto canonicalization_method = signed_info.append_child("CanonicalizationMethod");
    auto signature_method = signed_info.append_child("SignatureMethod");

    auto reference = signed_info.append_child("Reference");

    auto transforms = reference.append_child("Transforms");

    auto transform = transforms.append_child("Transform");

    auto digest_method = reference.append_child("DigestMethod");
    auto digest_value = reference.append_child("DigestValue");

    auto signature_value = signature.append_child("SignatureValue");

    auto key_info = signature.append_child("KeyInfo");

    auto x509_data = key_info.append_child("X509Data");

    auto x509_subject_name = x509_data.append_child("X509SubjectName");
    auto x509_certificate = x509_data.append_child("X509Certificate");

    //Setting values for all CMAC document nodes.
    cmac_protocol_version.text().set("1.0");
    cmac_sending_gateway_id.text().set(cap_message.child("sender").text().get()); //TODO: Determine how to get gateway IP?
    cmac_message_number.text().set(cap_message.child("identifier").text().get()); //TODO: Determining how to identify CMSP-initiated value, when applicable.
    cmac_special_handling.text().set(cap_message.child("scope").text().get()); //TODO: Ensure correctness.
    cmac_sender.text().set(cap_message.child("sender").text().get());
    cmac_sent_date_time.text().set(date_time_str.c_str());
    cmac_status.text().set(cap_message.child("status").text().get());
    cmac_message_type.text().set(cap_message.child("msgType").text().get());
    cmac_response_code.text().set(cap_message.child("info").child("responseType").text().get());

    if (cap_message.child("note")) {
        cmac_note.text().set(cap_message.child("note").text().get());
    }

    cmac_cap_alert_uri.text().set("Temp value"); //TODO: Determine how to obtain from the gateway.
    cmac_cap_identifier.text().set(cap_message.child("identifier").text().get());
    cmac_cap_sent_date_time.text().set(cap_message.child("sent").text().get());

    cmac_category.text().set(cap_message.child("info").child("category").text().get());

    //TODO: Verify if this if-else is even necessary.
    std::string special_handling = cmac_special_handling.text().get();
    if (special_handling.compare("Presidential") == 0) {
        cmac_event_code.text().set("EAN");
    }
    else if (special_handling.compare("Child Abduction") == 0) {
        cmac_event_code.text().set("CAE");
    }
    else if (special_handling.compare("Required Monthly Test") == 0) {
        cmac_event_code.text().set("RMT");
    }

    cmac_response_type.text().set(cap_message.child("info").child("responseType").text().get());
    cmac_severity.text().set(cap_message.child("info").child("severity").text().get());
    cmac_urgency.text().set(cap_message.child("info").child("urgency").text().get());
    cmac_certainty.text().set(cap_message.child("info").child("certainty").text().get());
    cmac_expires_date_time.text().set(cap_message.child("info").child("expires").text().get());
    cmac_sender_name.text().set(cap_message.child("info").child("senderName").text().get());

    if (cap_message.child("language")) {
        cmac_text_language.text().set(cap_message.child("language").text().get());
    }

    std::string alert_message = cap_message.child("info").child("description").text().get();
    cmac_text_alert_message_length.text().set(alert_message.length());
    cmac_text_alert_message.text().set(cap_message.child("info").child("description").text().get());

    //Saving CMAC document.
    bool saved = cmac_doc.save_file(cmac_filename.c_str());
}

int main() {
    CMAC::convert("soap_message_test.xml", "test.xml");
}


