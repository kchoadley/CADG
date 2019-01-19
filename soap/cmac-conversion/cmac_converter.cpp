// Created by Ross on 1/18/2019.
// Currently only reads in an existing SOAP file
// into memory and displays the status node to prove read functionality.

#include <iostream>
#include <string>
#include "cmac_converter.hpp"
#include "../pugixml-1.9/src/pugixml.hpp"
#include "../pugixml-1.9/src/pugixml.cpp"

int main() {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("soap_message_test.xml");
    pugi::xml_node soap_message = doc.first_child().first_child().first_child();

    std::cout << "SOAP Status: " << soap_message.child("status").text().get() << std::endl;
}


