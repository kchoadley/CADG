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

    //Setting values for all CMAC document nodes.
    cmac_protocol_version.text().set("1.0");

    //Saving CMAC document.
    bool saved = cmac_doc.save_file(cmac_filename.c_str());
}

int main() {
    CMAC::convert("soap_message_test.xml", "test.xml");
}


