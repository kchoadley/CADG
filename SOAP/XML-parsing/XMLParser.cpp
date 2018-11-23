// Created by Ross on 11/21/18.
// Base solution modified from the following tutorial:
// https://akrzemi1.wordpress.com/2011/07/13/parsing-xml-with-boost/
// (NOTE: This file will likely change dramatically over time. This
// version is intended to develop and display future functionality
// on test values.)

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "XMLParser.h"
#include <boost/foreach.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>

struct coordinate {
    double x;
    double y;
};

struct CAPCode {
    std::string valueName;
    std::string value;
};

struct CAPArea {
    std::string areaDesc;
    std::vector<coordinate> polygon;
    std::vector<CAPCode> geoCode;
};

struct CAPMessage {
    std::string identifier;
    std::string sender;
    std::string sent;
    std::string status;
    std::string msgType;
    std::string scope;

    std::string category;
    std::string event;
    std::string responseType;
    std::string urgency;
    std::string severity;
    std::string certainty;
    //CAPCode eventCode; Commenting out until further development is complete.
    std::string expires;
    std::string senderName;
    std::string headline;
    std::string description;
    std::string instruction;
    //CAPArea area; Commenting out until further development is complete.
};

//typedef std::vector<User> Users;

CAPMessage readXML(std::istream & is) {
    using boost::property_tree::ptree;
    ptree pt;
    read_xml(is, pt);

    CAPMessage parsedXML;
    parsedXML.identifier = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.identifier");
    parsedXML.sender = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.sender");
    parsedXML.sent = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.sent");
    parsedXML.status = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.status");
    parsedXML.msgType = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.msgType");
    parsedXML.scope = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.scope");
    parsedXML.category = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.category");
    parsedXML.event = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.event");
    parsedXML.responseType = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.responseType");
    parsedXML.urgency = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.urgency");
    parsedXML.certainty = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.certainty");
    parsedXML.expires = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.expires");
    parsedXML.senderName = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.senderName");
    parsedXML.headline = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.headline");
    parsedXML.description = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.description");
    parsedXML.instruction = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.instruction");
//    BOOST_FOREACH(ptree::value_type const& value, pt.get_child("SOAP-ENV:Body")) {
//        if(value.first == "user") {
//            User parsedUser;
//            parsedUser.name = value.second.get<std::string>("name");
//            parsedUser.age = value.second.get<int>("age");
//            parsedXML.push_back(parsedUser);
//        }
//    }
    return parsedXML;
}

void writeXML(Users users, std::ostream & os) {
    using boost::property_tree::ptree;
    ptree pt;

    pt.add("users.version", 2);

    BOOST_FOREACH(User user, users) {
        ptree & node = pt.add("users.user", "");

        node.put("name", user.name);
        node.put("age", user.age);
    }
    write_xml(os, pt);
}

int main() {
    std::ifstream input("usersTest.xml");
    Users users = readXML(input);

    std::ofstream output("usersTestOutput.xml");
    writeXML(users, output);
    return 0;
}