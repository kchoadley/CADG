/// A REST endpoint controller implementation class for CMSP Gateways
/**
 * CMSPController implements the interface defined by the Controller class.
 * This represents an endpoint in the Rest Server for
 * receiving data about CMSP Gateways.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 *
 * @file        cmsp_controller.hpp
 * @authors     Vaniya Agrawal
 * @date        January, 2019
 */

#ifndef CMSP_CONTROLLER_HPP
#define CMSP_CONTROLLER_HPP
#include <controller.hpp>
#include "data_access_interface.hpp"
using cadg_rest::DataAccessInterface;

namespace cadg_rest {
    class CMSPController: public Controller {
    public:
        CMSPController(CMSPController& logger__, DataAccessInterface& dao__) : dao__(dao__), Controller(logger__) {}
        ~CMSPController() { }
        void InitHandlers() override;
        void HandleGet(http_request message) override;
        void HandlePut(http_request message) override;
        void HandlePost(http_request message) override;
        void HandleDelete(http_request message) override;
    private:
        DataAccessInterface& dao__;
    };
}
#endif //CMSP_CONTROLLER_HPP
