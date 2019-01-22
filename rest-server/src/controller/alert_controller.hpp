/// A REST endpoint controller implementation class for alerts
/**
 * AlertController implements the interface defined by the Controller class.
 * This represents an endpoint in the Rest Server for receiving and sending
 * data about alerts. Alert data can only be sent and received - not updated
 * or deleted.
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
    /// Returns the requested alert(s).
    /**
     * HandleGet returns an alert or collection of alerts determined
     * by the parameters in the URL path.
     * If there is no URL path, this returns all alerts.
     * If there is an alert id, or another search parameter, this returns
     * all alerts that match the search key.
     *
     * @param message   The http request message to be parsed.
     */
    void HandleGet(http_request message) override;
    /// Creates a new alert.
    /**
     * HandlePost adds a new alert based on information provided
     * in the body of the http_request (in json format). This method
     * forwards the message along for conversion to CMAC and CMSP distribution.
     *
     * @param message   The http request message that includes the alert info in
     *                  json format with the body.
     */
    void HandlePost(http_request message) override;
private:
    DataAccessInterface& dao__;
};
}
#endif //ALERT_CONTROLLER_HPP
