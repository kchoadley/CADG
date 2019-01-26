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
        /**
         * Handles incoming GET http requests on the Aog endpoint. Replies to message directly with
         * requested information based on passed queries. Used to get information on Aogs
         * @param message incoming http message request
         */
        void HandleGet(http_request message) override;
        /**
         * Handles incoming PUT http requests on the Aog endpoint. Replies to message directly with
         * success or failure. Used to update information on Aogs in the database
         * @param message
         */
        void HandlePut(http_request message) override;
        /**
         * Handles incoming POST http requests on the Aog endpoint. Replies to message directly with
         * success or failure. Used to add new Aogs to the database
         * @param message
         */
        void HandlePost(http_request message) override;
        /**
         * Handles incoming DELETE http requests on the Aog endpoint. Replies to message directly with
         * success or failure. Used to delete Aogs from the database
         * @param message
         */
        void HandleDelete(http_request message) override;

    private:
        AogDaoInterface& dao__;
    };

}  // namespace cadg_rest

#endif //REST_SERVER_AOG_CONTROLLER_HPP