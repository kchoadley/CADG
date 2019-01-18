/// A REST endpoint controller implementation class for alerts
/**
 * AlertController implements the interface defined by the Controller class.
 * This represents an endpoint in the Rest Server for receiving data about alerts.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 *
 * @file        alert_controller.hpp
 * @authors     Vaniya Agrawal
 * @date        January, 2019
 */

#ifndef ALERT_CONTROLLER_HPP
#define ALERT_CONTROLLER_HPP
#include <controller.hpp>
#include "data_access_interface.hpp"
using cadg_rest::DataAccessInterface;

namespace cadg_rest {
class AlertController: public Controller {
public:
    AlertController(AlertController& logger__, DataAccessInterface& dao__) : dao__(dao__), Controller(logger__) {}
    ~AlertController() { }
    void InitHandlers() override;
    void HandleGet(http_request message) override;
    void HandlePut(http_request message) override;
    void HandlePost(http_request message) override;
    void HandleDelete(http_request message) override;
private:
    DataAccessInterface& dao__;
};
}
#endif //ALERT_CONTROLLER_HPP
