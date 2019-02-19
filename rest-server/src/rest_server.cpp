/// Runs the REST server
/**
 * Used to initialize and start the REST server.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley, Shawn Hulce, Michael McCulley
 *
 * @file        rest_server.cpp
 * @authors     Kristofer Hoadley
 * @date        November, 2018
 */
#include <iostream>
#include <string>
#include "admin_controller.hpp"
#include "admin_dao.hpp"
#include "alert_dao.hpp"
#include "aog_dao.hpp"
#include "logger.hpp"
#include "aog_controller.hpp"
#include "log_level.hpp"
#include "alert_controller.hpp"
#include "soap_controller.hpp"
using cadg_rest::AlertDao;
using cadg_rest::AdminController;
using cadg_rest::AdminDao;
using cadg_rest::AogDao;
using cadg_rest::Logger;
using cadg_rest::LoggerInterface;
using cadg_rest::AogController;
using cadg_rest::AlertController;
using cadg_rest::LogLevel;
using cadg_soap::SoapController;

std::string getEnvVar(std::string const& key) {
    char const* val = getenv(key.c_str());
    return val == NULL ? std::string() : std::string(val);
}
int main(int argc, const char * argv[]) {
    LoggerInterface& logger(Logger::Instance());
    logger.LogLevel(LogLevel::DEBUG);
    logger.Log(LogLevel::INFO, "Starting cadg rest server");
    AlertController alert_controller(AlertDao::Instance());
    AdminController admin_controller(AdminDao::Instance());
    AogController aog_controller(AogDao::Instance());
    SoapController soap_controller;
    std::string server_address;
    if (argc > 2)
        server_address.append(argv[2]);
    else
        server_address.append("http://host_auto_ip4");
    if (argc > 1)
        server_address.append(argv[1]);
    else
        server_address.append(":8080");
    server_address.append("/v1/cadg/api");
    admin_controller.endpoint(server_address + "/admins");
    alert_controller.endpoint(server_address + "/alerts");
    aog_controller.endpoint(server_address + "/aogs");
    soap_controller.endpoint("http://host_auto_ip4:8080/cadg/soap/alerts");
    try {
        admin_controller.Accept().wait();
        aog_controller.Accept().wait();
        alert_controller.Accept().wait();
        soap_controller.Accept().wait();
        logger.Log(LogLevel::INFO, "Listening for requests at: " +  alert_controller.endpoint());
        logger.Log(LogLevel::INFO, "Listening for requests at: " +  admin_controller.endpoint());
        logger.Log(LogLevel::INFO, "Listening for requests at: " + aog_controller.endpoint());
        logger.Log(LogLevel::INFO, "Listening for requests at: " + soap_controller.endpoint());
        logger.Log(LogLevel::INFO, "Press ENTER to exit.");
        std::string line;
        std::getline(std::cin, line);
        admin_controller.Shutdown().wait();
        alert_controller.Shutdown().wait();
        aog_controller.Shutdown().wait();
        soap_controller.Shutdown().wait();
    }
    catch(std::exception&  e) {
        logger.Log(LogLevel::ERR, "There was an error");
        logger.Log(LogLevel::ERR, e.what());
    }
    return 0;
}
