///Parses existing SOAP XML documents and generates new CMAC XML documents.
/**
 * This class has two primary functions: Reading and writing XML documents.
 * The read functionality parses an existing SOAP XML document and stores
 * it in memory for future use via a CAPMessage struct. The write functionality
 * uses this struct to build a new CMAC XML document.
 * Base solution modified from the following tutorial:
 * https://akrzemi1.wordpress.com/2011/07/13/parsing-xml-with-boost/
 *
 * @file        XMLParser.cpp
 * @authors     Ross Arcemont
 * @date        November, 2018
 */
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "XMLParser.hpp"
#include <boost/foreach.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>

///Represents a single coordinate pair used in CAPArea polygons.
struct coordinate {
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
    std::string areaDesc;
    //TODO: Implement polygon as a vector of coordinates instead of a string.
    //std::vector<coordinate> polygon; Temporarily stored as a string due to time constraints. Will update in next iteration.
    std::string polygon;
    std::vector<CAPCode> geoCode;
};

///Represents the CAP message content held within the SOAP message body. Also used to create the corresponding CMAC message.
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

/**
 * newMessage is used to store the incoming CAP message
 * held within the SOAP message body into memory. Once
 * all attributes in newMessage are defined, it is used
 * to build a new CMAC message compatible for CMSP use.
 */
typedef CAPMessage newMessage;

///Reads an existing SOAP message and makes its CAP content available for use by the system.
/**
 * Uses an istream to read in an existing XML file structured
 * in the SOAP schema. Once the XML file is fully read into
 * memory, the SOAP body, AKA the CAP message, is parsed into
 * a new CAPMessage struct for future use by the writeXML method.
 *
 * @param is    Input stream of the incoming SOAP XML file.
 * @return      New CAPMessage with fully defined attributes.
 */
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

///Takes in a fully defined CAPMessage struct, creates a new CMAC message from it, and writes it to the file system as an XML file.
/**
 * Uses a fully defined CAPMessage struct to define the content of a new CMAC message.
 * Once all key fields are defined in the CMAC message, the function uses an ostream
 * to write the CMAC message to the file system as an XML file.
 *
 * @param newMessage    Fully defined CAPMessage struct used to create the CMAC message.
 * @param os            Output stream for the CMAC XML file creation process.
 */
void writeXML(CAPMessage newMessage, std::ostream & os) {
    using boost::property_tree::ptree;
    ptree pt;

    //TODO: Replace all hard-coded values with system-generated values.
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
//
//int main() {
//    std::ifstream input("SOAPMessageTest.xml");
//    CAPMessage newMessage = readXML(input);
//
//    std::ofstream output("testCMACMessage.xml");
//    writeXML(newMessage, output);
//    return 0;
//}