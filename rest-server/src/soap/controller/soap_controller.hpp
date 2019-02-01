// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
// Created by Shawn on 11/26/2018.
//

#ifndef SOAP_CONTROLLER_HPP
#define SOAP_CONTROLLER_HPP
#include <controller.hpp>
#include <data_access_interface.hpp>
#include "../../gSoapFiles/CAP/soapH.h"
using cadg_rest::DataAccessInterface;

namespace cadg_soap {
class SoapController: public cadg_rest::Controller {

    public:
        SoapController(cadg_rest::LoggerInterface& logger__, cadg_rest::DataAccessInterface& dao__) : dao__(dao__), Controller(logger__) {

        }
        ~SoapController() {}

    void InitHandlers() override;
    void HandleGet(http_request message) override;
    void HandlePut(http_request message) override;
    void HandlePost(http_request message) override;
    void HandleDelete(http_request message) override;
    private:
    DataAccessInterface& dao__;
};

} //end cadg_soap
#endif //CADG_REST_SERVER_SOAP_CONTROLLER_HPP
