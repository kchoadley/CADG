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
    //std::vector<coordinate> polygon; Temporarily stored as a string due to time constraints. Will update in next iteration.
    std::string polygon;
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
    CAPCode eventCode;
    std::string expires;
    std::string senderName;
    std::string headline;
    std::string description;
    std::string instruction;
    std::string contact;
    CAPArea area;
};

typedef CAPMessage newMessage;

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
    parsedXML.eventCode.valueName = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.eventCode.valueName");
    parsedXML.eventCode.value = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.eventCode.value");
    parsedXML.expires = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.expires");
    parsedXML.senderName = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.senderName");
    parsedXML.headline = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.headline");
    parsedXML.description = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.description");
    parsedXML.instruction = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.instruction");
    parsedXML.contact = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.contact");
    parsedXML.area.areaDesc = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.area.areaDesc");
    parsedXML.area.polygon = pt.get<std::string>("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info.area.polygon");

    //This method is modified from the first response of the following StackOverflow post:
    //https://stackoverflow.com/questions/40393765/accessing-multi-valued-keys-in-property-tree
    auto &infoRoot = pt.get_child("SOAP-ENV:Envelope.SOAP-ENV:Body.alert.info");
    for (auto &areaChild : infoRoot.get_child("area")) {
        if (areaChild.first == "geocode") {
            CAPCode newGeoCode;
            newGeoCode.valueName = areaChild.second.get<std::string>("valueName");
            newGeoCode.value = areaChild.second.get<std::string>("value");
            parsedXML.area.geoCode.push_back(newGeoCode);
        }
    }
    return parsedXML;
}

void writeXML(CAPMessage newMessage, std::ostream & os) {
    using boost::property_tree::ptree;
    ptree pt;

    pt.add("CMAC_Alert_Attributes.CMAC_protocol_version", 1.0);
    pt.add("CMAC_Alert_Attributes.CMAC_sending_gateway_id", "localhost");
    pt.add("CMAC_Alert_Attributes.CMAC_message_number", "mvjfo92513");
    pt.add("CMAC_Alert_Attributes.CMAC_special_handling", "Public Safety message");
    pt.add("CMAC_Alert_Attributes.CMAC_sender", newMessage.sender);
    pt.add("CMAC_Alert_Attributes.CMAC_sent_date_time", newMessage.sent);
    pt.add("CMAC_Alert_Attributes.CMAC_status", newMessage.status);
    pt.add("CMAC_Alert_Attributes.CMAC_message_type", newMessage.msgType);
    pt.add("CMAC_Alert_Attributes.CMAC_response_code", newMessage.responseType);
    pt.add("CMAC_Alert_Attributes.CMAC_cap_alert_uri", "localhost/alerturi");
    pt.add("CMAC_Alert_Attributes.CMAC_cap_identifier", newMessage.identifier);
    pt.add("CMAC_Alert_Attributes.CMAC_cap_sent_date_time", newMessage.sent);
    pt.add("CMAC_Alert_Attributes.CMAC_alert_info.CMAC_category", newMessage.category);
    pt.add("CMAC_Alert_Attributes.CMAC_alert_info.CMAC_event_code", "TestCode");
    pt.add("CMAC_Alert_Attributes.CMAC_alert_info.CMAC_response_type", newMessage.responseType);
    pt.add("CMAC_Alert_Attributes.CMAC_alert_info.CMAC_severity", newMessage.severity);
    pt.add("CMAC_Alert_Attributes.CMAC_alert_info.CMAC_urgency", newMessage.urgency);
    pt.add("CMAC_Alert_Attributes.CMAC_alert_info.CMAC_certainty", newMessage.certainty);
    pt.add("CMAC_Alert_Attributes.CMAC_alert_info.CMAC_expires_date_time", newMessage.expires);
    pt.add("CMAC_Alert_Attributes.CMAC_alert_info.CMAC_sender_name", newMessage.senderName);
    pt.add("CMAC_Alert_Attributes.CMAC_alert_info.CMAC_text_language", "English");
    pt.add("CMAC_Alert_Attributes.CMAC_alert_info.CMAC_text_alert_message_length", newMessage.description.length());
    pt.add("CMAC_Alert_Attributes.CMAC_alert_info.CMAC_text_alert_message", newMessage.description);
    pt.add("CMAC_Alert_Attributes.CMAC_alert_info.CMAC_Alert_Area.CMAC_area_description", "United States");
    pt.add("CMAC_Alert_Attributes.CMAC_alert_info.CMAC_Alert_Area.CMAC_cmas_geocode", newMessage.eventCode.value);
    pt.add("CMAC_Alert_Attributes.CMAC_alert_info.CMAC_Alert_Area.CMAC_cap_geocode.valueName", newMessage.eventCode.valueName);
    pt.add("CMAC_Alert_Attributes.CMAC_alert_info.CMAC_Alert_Area.CMAC_cap_geocode.value", newMessage.eventCode.value);
    pt.add("CMAC_Alert_Attributes.CMAC_Digital_Signature.Signature.SignedInfo.CanonicalizationMethod", "Algorithm=\"http://www.w3.org/2001/10/xml-exc-c14n#\"");
    pt.add("CMAC_Alert_Attributes.CMAC_Digital_Signature.Signature.SignedInfo.SignatureMethod", "Algorithm=\"http://www.w3.org/2001/04/xmldsig-more#rsa-sha256\"");
    pt.add("CMAC_Alert_Attributes.CMAC_Digital_Signature.Signature.SignedInfo.Reference.Transform.Transform", "Algorithm=\"http://www.w3.org/2000/09/xmldsig#enveloped-signature\"");
    pt.add("CMAC_Alert_Attributes.CMAC_Digital_Signature.Signature.SignedInfo.Reference.DigestMethod", "Algorithm=\"http://www.w3.org/2001/04/xmlenc#sha256\"");
    pt.add("CMAC_Alert_Attributes.CMAC_Digital_Signature.Signature.SignedInfo.Reference.DigestValue", "TestValue");
    pt.add("CMAC_Alert_Attributes.CMAC_Digital_Signature.Signature.SignatureValue", "TestSignatureValue");
    pt.add("CMAC_Alert_Attributes.CMAC_Digital_Signature.Signature.KeyInfo.X509Data.X509SubjectName", "TestX509SubjectName");
    pt.add("CMAC_Alert_Attributes.CMAC_Digital_Signature.Signature.KeyInfo.X509Data.X509Certificate", "TestX509Certificate");

    write_xml(os, pt);
}

int main() {
    std::ifstream input("SOAPMessageTest.xml");
    CAPMessage newMessage = readXML(input);

    std::ofstream output("testCMACMessage.xml");
    writeXML(newMessage, output);
    return 0;
}