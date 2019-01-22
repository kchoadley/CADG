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
        /// Returns the CMSP, or collection of CMSPs, requested.
        /**
         * A plain GET request will return a collection of all CMSPs in
         * the system. An extended URI will search on cmspID, while a
         * query string will search on the keys passed (agency, name, scope).
         * GET all CMSPs (/cmsps)
         * GET specific CMSPs (/cmsps/{id})
         * GET filtered CMSPs (/cmsps?name=SprintGW)
         *
         * @param message The http request message to be parsed.
         */
        void HandleGet(http_request message) override;
        /// Updates the specified CMSP with the provided information
        /**
         * A PUT request will specify in the URI the id of the CMSP being
         * modified and send the information that needs to be updated. For example:
         * {
         *      name: updatedName,
         *      agency: updatedAgency,
         * }

         * @param message   The http request message that contains the CMSP info
         *                  in json format within the body.
         */
        void HandlePut(http_request message) override;
        /// Creates a new CMSP with the provided information
        /**
         * A POST request will include all the CMSP details. For example:
         * {
         *      name: SprintGW,
         *      agency: Sprint Communications,
         *      ...
         * }
         * @param message   The http request message that contains the CMSP info
         *                  in json format within the body.
         */
        void HandlePost(http_request message) override;
        /// Deletes the specified CMSP
        /**
         * A DELETE request will specify in the URI, the id of the CMSP being deleted.
         * The ID should be specified in the URL path.
         * @param message   The http request message to be parsed.
         */
        void HandleDelete(http_request message) override;
    private:
        DataAccessInterface& dao__;
    };
}
#endif //CMSP_CONTROLLER_HPP
