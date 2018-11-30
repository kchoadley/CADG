//
// Created by Ross on 11/29/2018.
//

#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include "xml_parser.hpp"

TEST(xml_parse_tests, import) {
    std::ifstream input("soap_message_test.xml");
    CAPMessage test_message = ReadXML(input);
    EXPECT_EQ(test_message.identifier, "KSTO1055887203");
    EXPECT_EQ(test_message.sender, "KSTO@NWS.NOAA.GOV");
    EXPECT_EQ(test_message.sent, "2003-06-17T14:57:00-07:00");
    EXPECT_EQ(test_message.status, "Actual");
    EXPECT_EQ(test_message.msg_type, "Alert");
    EXPECT_EQ(test_message.scope, "Public");
}