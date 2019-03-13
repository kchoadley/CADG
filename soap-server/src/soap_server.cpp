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
#include "gSOAPFiles/soapCAPSoapHTTPService.h"
#include "gSOAPFiles/soapStub.h"
#include "gSOAPFiles/soapH.h"
#include "gSOAPFiles/stdsoap2.h"
#include "gSOAPFiles/CAPSoapHttp.nsmap"
using cadg_soap::LoggerInterface;
using cadg_soap::LogLevel;
using cadg_soap::Logger;

int main(int argc, const char * argv[]) {
    int port = 8000;
    if (std::strlen(*argv) == 1 ) {
        port = std::stoi(argv[0]);
    }
    LoggerInterface& logger(Logger::Instance());
    logger.LogLevel(LogLevel::DEBUG);
    struct soap soap;
    CAPSoapHttpService service(&soap);

    service.soap->send_timeout = service.soap->recv_timeout = 5; // 5 sec socket idle timeout
    service.soap->transfer_timeout = 30;                         // 30 sec message transfer timeout
    while (service.run(port))
        service.soap_stream_fault(std::cerr);
    service.destroy();
    return 0;

}

int CAPSoapHttpService::getRequest(ns2__requestParameterList *ns1__getRequestTypeDef,
                                   ns3__responseParameterList &ns1__getResponseTypeDef) {
    return SOAP_OK;
}

int CAPSoapHttpService::postCAP(_ns1__postCAPRequestTypeDef *ns1__postCAPRequestTypeDef,
                                _ns1__postCAPResponseTypeDef &ns1__postCAPResponseTypeDef) {
    return SOAP_OK;
}

int CAPSoapHttpService::getMessage(ns2__requestParameterList *ns1__getMessageTypeDef,
                                   _ns1__messageResponseTypeDef &ns1__messageResponseTypeDef) {
    return SOAP_OK;
}