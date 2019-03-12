/**
 * Operates the gSOAP SOAP server for the OS-WASABI CADG Project
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley, Shawn Hulce, Michael McCulley
 *
 * @file        rest_server.cpp
 * @authors     Shawn Hulce
 * @date        March 2019
 */
#include <iostream>
#include <string>
#include "log_level.hpp"
#include "logger.hpp"
using cadg_soap::LoggerInterface;
using cadg_soap::LogLevel;
using cadg_soap::Logger;

int main(int argc, const char * argv[]) {
    LoggerInterface& logger(Logger::Instance());
    logger.LogLevel(LogLevel::DEBUG);
    logger.Log(LogLevel::DEBUG, "TESTING CADG SOAP COMPILATION");
    return 0;
}