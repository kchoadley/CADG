// Created by Ross on 1/18/2019.
// Currently only reads in an existing SOAP file
// into memory and displays the status node to prove read functionality.

#include <iostream>
#include <string>
#include "cmac_converter.hpp"
#include "../pugixml-1.9/src/pugixml.hpp"
#include "../pugixml-1.9/src/pugixml.cpp"

void CMAC::convert(std::string soap_filename, std::string cmac_filename) {
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

    //Saving CMAC document.
    bool saved = cmac_doc.save_file(cmac_filename.c_str());
}

int main() {
    CMAC::convert("soap_message_test.xml", "test.xml");
}


