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
#include "soapCAPSoapHTTPService.h"
using cadg_soap::LoggerInterface;
using cadg_soap::LogLevel;
using cadg_soap::Logger;

int main(int argc, const char * argv[]) {
    int port = 8000
    if (argv == 1 ) {
        port = std::stoi(argv[0]);
    }
    LoggerInterface& logger(Logger::Instance());
    logger.LogLevel(LogLevel::DEBUG);
    CAPSoapHTTPService service();

    service.soap->send_timeout = service.soap->recv_timeout = 5; // 5 sec socket idle timeout
    service.soap->transfer_timeout = 30;                         // 30 sec message transfer timeout
    while (service.run(port))
        service.soap_stream_fault(std::cerr);
    service.destroy();
    return 0;

}