/**
 *  Alert Originator Groups API Endpoint Controller
 *
 * Copyright 2019   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley, Shawn Hulce, Michael McCulley
 *
 * @file        aog_controller.hpp
 * @authors     Shawn Hulce
 * @date        January 2019
 */

#ifndef REST_SERVER_AOG_CONTROLLER_HPP
#define REST_SERVER_AOG_CONTROLLER_HPP

#include <controller.hpp>
#include "aog_dao_interface.hpp"

using cadg_rest::AogDaoInterface;

namespace cadg_rest {
    class AogController: public Controller {
    public:
        AogController(LoggerInterface& logger__, AogDaoInterface& input_dao__) : dao__(input_dao__), Controller(logger__) {}

        ~AogController() { }

        void InitHandlers() override;

        void HandleGet(http_request message) override;

        void HandlePut(http_request message) override;

        void HandlePost(http_request message) override;

        void HandleDelete(http_request message) override;

    private:
        AogDaoInterface& dao__;
    };

}  // namespace cadg_rest

#endif //REST_SERVER_AOG_CONTROLLER_HPP