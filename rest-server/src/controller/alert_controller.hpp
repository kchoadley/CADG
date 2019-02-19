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

#ifndef ALERT_CONTROLLER_H
#define ALERT_CONTROLLER_H
#include <controller.hpp>
#include "alert_dao_interface.hpp"
using cadg_rest::AlertDaoInterface;

namespace cadg_rest {
class AlertController: public Controller {
public:
    AlertController(AlertDaoInterface& dao__) : dao__(dao__) { }
    ~AlertController() { }
    void InitHandlers() override;
    /// Returns the requested alert(s).
    /**
     * HandleGet request will return a collection of all alerts
     * in the system. An extended URI will search on alertID,
     * while a query string will search on the keys passed (category,
     * severity, or urgency).
     *
     * GET all alerts (/alerts)
     * GET specific alerts(/alerts/{id})
     * GET filtered alerts(/alerts?urgency=immediate)
     *
     * @param message   The http request message to be parsed.
     */
    void HandleGet(http_request message) override;
    /// Creates a new alert with the provided information and forwards it along.
    /**
     * HandlePost adds a new alert received in CAP format. This method
     * forwards the message along for conversion to CMAC and CMSP distribution.
     *
     * @param message   The http request message that includes the alert info in
     *                  json format with the body.
     */
    void HandlePost(http_request message) override;
    void HandlePut(http_request message) override;
    void HandleDelete(http_request message) override;

private:
    AlertDaoInterface& dao__;
};
}
#endif //ALERT_CONTROLLER_HPP
