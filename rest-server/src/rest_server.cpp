// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#include <iostream>
#include <string>
#include "data_access_object.hpp"
#include "logger.hpp"
#include "user_controller.hpp"
using cadg_rest::DataAccessObject;
using cadg_rest::Logger;
using cadg_rest::LoggerInterface;
using cadg_rest::UserController;

int main(int argc, const char * argv[]) {
    LoggerInterface& logger(Logger::Instance());
    logger.LogLevel(1);  // effectively log level of DEBUG, set to 2 or higher to filter out debug messages
    logger.Log(2, "Starting cadg rest server");
    UserController user_controller(Logger::Instance(), DataAccessObject::Instance());
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
    user_controller.endpoint(server_address + "/users");
    try {
        user_controller.Accept().wait();
        logger.Log(2, "Listening for requests at: " +  user_controller.endpoint());
        logger.Log(2, "Press ENTER to exit.");
        std::string line;
        std::getline(std::cin, line);
        user_controller.Shutdown().wait();
    }
    catch(std::exception&  e) {
        logger.Log(4, "There was an error");
       logger.Log(4, e.what());
    }
    return 0;
}
