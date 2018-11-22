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
#include "XMLParser.h"
#include <boost/foreach.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>

struct User {
    std::string name;
    int age;
};

typedef std::vector<User> Users;

Users readXML(std::istream & is) {
    using boost::property_tree::ptree;
    ptree pt;
    read_xml(is, pt);

    Users parsedXML;
    BOOST_FOREACH(ptree::value_type const& value, pt.get_child("users")) {
        if(value.first == "user") {
            User parsedUser;
            parsedUser.name = value.second.get<std::string>("name");
            parsedUser.age = value.second.get<int>("age");
            parsedXML.push_back(parsedUser);
        }
    }
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