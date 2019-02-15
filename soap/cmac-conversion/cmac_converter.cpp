#include <iostream>
#include <string>
#include <ctime>
#include "cmac_converter.hpp"
#include "../pugixml-1.9/src/pugixml.hpp"
#include "../pugixml-1.9/src/pugixml.cpp"

///Converts any syntactically correct SOAP CAP document into a CMAC XML document.
/**
 * Converts syntactically correct SOAP CAP documents into CMAC XML documents.
 * Pulls the SOAP XML document content in the soap_filename argument into memory
 * for content needed in the upcoming CMAC XML document structure. The CMAC
 * document structure is then created and filled with content from the
 * SOAP XML document before saving to the filepath and filename in the
 * cmac_filename argument.
 * @param soap_filename     Filepath and filename of the SOAP document to be converted
 * @param cmac_filename     Filepath and filename of the CMAC document to be saved
 */
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
    root_node.append_attribute("xmlns") = "\"cmac:2.0\""; //TODO: Check value. Potentially temporary.

    //Creating the node structure and node content for the CMAC_Alert_Attributes block.
    //All node variable names match the corresponding CMAC structure as closely as possible.
    auto cmac_protocol_version = root_node.append_child("CMAC_protocol_version");
    cmac_protocol_version.text().set("2.0"); //TODO: Determine how to get the protocol version based on either CAP message or other source.

    auto cmac_sending_gateway_id = root_node.append_child("CMAC_sending_gateway_id");
    cmac_sending_gateway_id.text().set("Temporary value"); //TODO: Determine how to get gateway IP or URI.

    auto cmac_message_number = root_node.append_child("CMAC_message_number");
    cmac_message_number.text().set(cap_message.child("identifier").text().get()); //TODO: Determining how to identify CMSP-initiated value, when applicable.

    //TODO: Complete when CMAC object is available.
    if (true) {
        auto cmac_referenced_message_number = root_node.append_child("CMAC_referenced_message_number");
        cmac_referenced_message_number.text().set("Temporary value");
    }

    //TODO: Complete when CMAC object is available.
    if (true) {
        auto cmac_referenced_message_cap_identifier = root_node.append_child("CMAC_referenced_message_cap_identifier");
        cmac_referenced_message_cap_identifier.text().set("Temporary value");
    }

    //TODO: Complete when CMAC object is available.
    if (true) {
        auto cmac_special_handling = root_node.append_child("CMAC_special_handling");
        cmac_special_handling.text().set(cap_message.child("scope").text().get()); //TODO: Ensure correctness.
    }

    //TODO: Complete when CMAC object is available.
    if (true) {
        auto cmac_sender = root_node.append_child("CMAC_sender");
        cmac_sender.text().set(cap_message.child("sender").text().get());
    }

    auto cmac_sent_date_time = root_node.append_child("CMAC_sent_date_time");
    cmac_sent_date_time.text().set(date_time_str.c_str());

    auto cmac_status = root_node.append_child("CMAC_status");
    cmac_status.text().set(cap_message.child("status").text().get());

    auto cmac_message_type = root_node.append_child("CMAC_message_type");
    cmac_message_type.text().set(cap_message.child("msgType").text().get());

    //TODO: Complete when CMAC object is available.
    //NOTE: Multiple occurrences possible
    if (true) {
        auto cmac_response_code = root_node.append_child("CMAC_response_code");
        cmac_response_code.text().set("Temporary value");
    }

    //TODO: Complete when CMAC object is available.
    //NOTE: Multiple occurrences possible
    if (true) {
        auto cmac_note = root_node.append_child("CMAC_note");
        cmac_note.text().set(cap_message.child("note").text().get());
    }

    //TODO: Complete when CMAC object is available.
    if (true) {
        auto cmac_cap_alert_uri = root_node.append_child("CMAC_cap_alert_uri");
        cmac_cap_alert_uri.text().set("Temporary value"); //TODO: Determine how to obtain from the gateway.
    }

    //TODO: Complete when CMAC object is available.
    if (true) {
        auto cmac_cap_identifier = root_node.append_child("CMAC_cap_identifier");
        cmac_cap_identifier.text().set(cap_message.child("identifier").text().get());
    }

    //TODO: Complete when CMAC object is available.
    if (true) {
        auto cmac_cap_sent_date_time = root_node.append_child("CMAC_cap_sent_date_time");
        cmac_cap_sent_date_time.text().set(cap_message.child("sent").text().get());
    }

    //Creating the node structure and node content for the CMAC_alert_info block.
    //All node variable names match the corresponding CMAC structure as closely as possible.
    //TODO: Complete when CMAC object is available.
    if (true) {
        auto cmac_alert_info = root_node.append_child("CMAC_alert_info");
        auto cmac_category = cmac_alert_info.append_child("CMAC_category");
        cmac_category.text().set(cap_message.child("info").child("category").text().get());

        //TODO: Complete when CMAC object is available.
        if (true) {
            auto cmac_response_type = cmac_alert_info.append_child("CMAC_response_type");
            cmac_response_type.text().set(cap_message.child("info").child("responseType").text().get());
        }

        auto cmac_severity = cmac_alert_info.append_child("CMAC_severity");
        cmac_severity.text().set(cap_message.child("info").child("severity").text().get());

        auto cmac_urgency = cmac_alert_info.append_child("CMAC_urgency");
        cmac_urgency.text().set(cap_message.child("info").child("urgency").text().get());

        auto cmac_certainty = cmac_alert_info.append_child("CMAC_certainty");
        cmac_certainty.text().set(cap_message.child("info").child("certainty").text().get());

        auto cmac_expires_date_time = cmac_alert_info.append_child("CMAC_expires_date_time");
        cmac_expires_date_time.text().set(cap_message.child("info").child("expires").text().get());

        //TODO: Complete when CMAC object is available.
        if (true) {
            auto cmac_sender_name = cmac_alert_info.append_child("CMAC_sender_name");
            cmac_sender_name.text().set(cap_message.child("info").child("senderName").text().get());
        }
    }


    //Creating the node structure and node content for the CMAC_Alert_Text block.
    //All node variable names match the corresponding CMAC structure as closely as possible.
    auto cmac_text_language = cmac_alert_info.append_child("CMAC_text_language");
    auto cmac_text_alert_message_length = cmac_alert_info.append_child("CMAC_text_alert_message_length");
    auto cmac_text_alert_message = cmac_alert_info.append_child("CMAC_text_alert_message");

    //Creating the node structure and node content for the CMAC_Alert_Area block.
    //All node variable names match the corresponding CMAC structure as closely as possible.
    auto cmac_alert_area = cmac_alert_info.append_child("CMAC_Alert_Area");
    auto cmac_area_description = cmac_alert_area.append_child("CMAC_area_description");
    auto cmac_polygon = cmac_alert_area.append_child("CMAC_polygon");
    auto cmac_cmas_geocode = cmac_alert_area.append_child("CMAC_cmas_geocode");

    //Creating geocode nodes and filling with content
    for (pugi::xml_node geocode = cap_message.child("info").child("area").first_child(); geocode ; geocode = geocode.next_sibling()) {
        std::string node_name = geocode.name();
        //std::cout << node_name << ' ';
        if(node_name.compare("geocode") == 0) {
            //std::cout << " made it ";
            auto cmac_cap_geocode = cmac_alert_area.append_child("CMAC_cap_geocode");
            auto value_name = cmac_cap_geocode.append_child("valueName");
            auto value = cmac_cap_geocode.append_child("value");

            value_name.text().set(geocode.child("valueName").text().get());
            value.text().set(geocode.child("value").text().get());
        }
    }

    //Creating the node structure and node content for the CMAC_Digital_Signature block.
    //All node variable names match the corresponding CMAC structure as closely as possible.
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
    if (cap_message.child("language")) {
        cmac_text_language.text().set(cap_message.child("language").text().get());
    }

    std::string alert_message = cap_message.child("info").child("description").text().get();
    cmac_text_alert_message_length.text().set(alert_message.length());
    cmac_text_alert_message.text().set(cap_message.child("info").child("description").text().get());

    cmac_area_description.text().set(cap_message.child("info").child("area").child("areaDesc").text().get());
    if (cap_message.child("info").child("area").child("polygon")) {
        cmac_polygon.text().set(cap_message.child("info").child("area").child("polygon").text().get());
    }
    cmac_cmas_geocode.text().set(cap_message.child("info").child("area").child("polygon").text().get());

    canonicalization_method.append_attribute("Algorithm");
    canonicalization_method.attribute("Algorithm") = "http://www.w3.org/2001/10/xml-exc-c14n#";
    signature_method.append_attribute("Algorithm");
    signature_method.attribute("Algorithm") = "http://www.w3.org/2001/04/xmldsig-more#rsa-sha256";
    reference.append_attribute("URI");
    transform.append_attribute("Algorithm");
    transform.attribute("Algorithm") = "http://www.w3.org/2000/09/xmldsig#enveloped-signature";
    digest_method.append_attribute("Algorithm");
    digest_method.attribute("Algorithm") = "http://www.w3.org/2001/04/xmlenc#sha256";

    //Assigning temporary values for currently unknown information.
    digest_value.text().set("Temporary value");
    signature_value.text().set("Temporary value");
    x509_subject_name.text().set("Temporary value");
    x509_certificate.text().set("Temporary value");


    //Saving CMAC document.
    bool saved = cmac_doc.save_file(cmac_filename.c_str());
}

//int main() {
//    CMAC::convert("soap_message_test.xml", "test.xml");
//}