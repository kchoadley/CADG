///Test class to display XML parsing and generation using the Boost library.
/**
 * This class is used as a means to test XML parsing and generation
 * techniques quickly and easily by providing a simple set of data
 * to test with. See the individual methods for more information.
 * Base solution modified from the following tutorial:
 * https://akrzemi1.wordpress.com/2011/07/13/parsing-xml-with-boost/
 *
 * @file        UsersXMLParseTest.cpp
 * @authors     Ross Arcemont
 * @date        November, 2018
 */
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "xml_parser.hpp"
#include <boost/foreach.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>

///Represents a simple user for example testing
struct User {
    std::string name;
    int age;
};

/**
 * Users stores the information of every user found
 * within the usersTest.xml file in memory.
 */
typedef std::vector<User> Users;

///Reads in and parses the usersTest.xml document for system use.
/**
 * Uses an istream to read in usersTest.xml. Once the XML file is
 * fully read into memory, it is parsed into a new Users vector
 * for future use by the writeXML method.
 *
 * @param is    Input stream of the incoming usersTest.xml file.
 * @return      New Users vector containing all information from usersTest.xml.
 */
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

///Takes in a Users vector, creates a new test XML structure from it, and writes it to the file system as an XML file.
/**
 * Uses a Users vector to define the content of a new test XML file.
 * Once all users information is defined in the new XML structure,
 * the function uses an ostream to write the structure to the file
 * system as an XML file.
 *
 * @param newMessage    Fully defined CAPMessage struct used to create the CMAC message.
 * @param os            Output stream for the CMAC XML file creation process.
 */
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
    std::ifstream input("users_test.xml");
    Users users = readXML(input);

    std::ofstream output("users_test_output.xml");
    writeXML(users, output);
    return 0;
}