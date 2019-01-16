//
// Created by shulce on 1/16/19.
//

#ifndef REST_SERVER_AOG_CONTROLLER_HPP
#define REST_SERVER_AOG_CONTROLLER_HPP

#endif //REST_SERVER_AOG_CONTROLLER_HPP

#include <controller.hpp>
#include "data_access_interface.hpp"

using cadg_rest::DataAccessInterface;

namespace cadg_rest {
    class AogController: public Controller {
    public:
        AogController(LoggerInterface& logger__, DataAccessInterface& dao__) : dao__(dao__), Controller(logger__) {}

        ~AogController() { }

        void InitHandlers() override;

        void HandleGet(http_request message) override;

        void HandlePut(http_request message) override;

        void HandlePost(http_request message) override;

        void HandleDelete(http_request message) override;

    private:
        DataAccessInterface& dao__;
    };

} // end cadg_rest