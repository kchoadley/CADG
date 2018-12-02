//TODO: Implement this file and create a proper class out of the XMLParser functionality.
//NOTE: All documentation is temporarily duplicated from XMLParser.cpp until
//XMLParser.h is fully implemented.
///Parses existing SOAP XML documents and generates new CMAC XML documents.
/**
 * This class has two primary functions: Reading and writing XML documents.
 * The read functionality parses an existing SOAP XML document and stores
 * it in memory for future use via a CAPMessage struct. The write functionality
 * uses this struct to build a new CMAC XML document.
 * Base solution modified from the following tutorial:
 * https://akrzemi1.wordpress.com/2011/07/13/parsing-xml-with-boost/
 *
 * @file        XMLParser.hpp
 * @authors     Ross Arcemont
 * @date        November, 2018
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#ifndef CADG_XMLPARSER_H
#define CADG_XMLPARSER_H
///Represents a single coordinate pair used in CAPArea polygons.
struct Coordinate {
    double x;
    double y;
};

///Represents either an event code or geo code in SOAP and CMAC messages.
struct CAPCode {
    std::string valueName;
    std::string value;
};

///Represents the specified area in SOAP and CMAC messages.
struct CAPArea {
    std::string area_desc;
    //TODO: Implement polygon as a vector of coordinates instead of a string.
    //std::vector<Coordinate> polygon; Temporarily stored as a string due to time constraints. Will update in next iteration.
    std::string polygon;
    std::vector<CAPCode> geo_code;
};

///Represents the CAP message content held within the SOAP message body. Also used to create the corresponding CMAC message.
struct CAPMessage {
    std::string identifier;
    std::string sender;
    std::string sent;
    std::string status;
    std::string msg_type;
    std::string scope;

    std::string category;
    std::string event;
    std::string response_type;
    std::string urgency;
    std::string severity;
    std::string certainty;
    CAPCode event_code;
    std::string expires;
    std::string sender_name;
    std::string headline;
    std::string description;
    std::string instruction;
    std::string contact;
    CAPArea area;
};

CAPMessage ReadXML(std::istream & is);
void WriteXML(CAPMessage new_message, std::ostream & os);
#endif //CADG_XMLPARSER_H
