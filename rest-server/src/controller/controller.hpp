/// A REST endpoint controller abstract class.
/**
 * Controller is a base class for REST controller classes, 
 * it has some common methods defined and leaves methods that
 * need to be defined by parent classes undefined. A controller
 * has an endpoint, can be started with Accept and ended with 
 * Shutdown. The default supported http verbs are GET, PUT, POST,
 * and DELETE.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 *
 * @file        controller.hpp
 * @authors     { Kristofer Hoadley }
 * @date        November, 2018
 */
#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <map>
#include <string>
#include <vector>
#include <cpprest/http_listener.h>
#include <cpprest/http_msg.h>
#include <pplx/pplxtasks.h>
#include "logger_interface.hpp"
#include "logger.hpp"
using namespace web;
using namespace http;
using namespace http::experimental::listener;

namespace cadg_rest {
/// A REST endpoint controller abstract class.
/**
 * Controller is a base class for REST controller classes, 
 * it has some common methods defined and leaves methods that
 * need to be defined by parent classes undefined. A controller
 * has an endpoint, can be started with Accept and ended with 
 * Shutdown. The default supported http verbs are GET, PUT, POST,
 * and DELETE.
 * Uses a Logger with LogNetworkActivity for logging.
 */
class Controller {
  public: 
    /// Takes in a Logger object reference that adheres to the Logger interface.
    Controller() : logger__(Logger::Instance()) { }
    Controller(LoggerInterface& logger__) : logger__(logger__) { }
    ~Controller() { }

    void endpoint(const std::string& endpoint);
    std::string endpoint() const;
    ///Starts the controller
    /**
     * Starts the controller listening at it's endpoint.
     * The endpoint should be set first.
     */
    pplx::task<void> Accept();
    /// Stops the controller from listening at it's endoint.
    pplx::task<void> Shutdown();
    /// Queries parses the provided query string of a URL path.
    /**
     * The queries are parsed with '&' delimiting queries
     * and with '=' delimiting values from keys.
     * 
     * @param query_string The path query string to be parsed.
     * @return A <string, string> map of query name as keys and variable as value.
     */
    static std::map<std::string, std::string> Queries(std::string query_string);

    ///Initializes listeners and binds methods to proper handlers.
    /**
     * Binds supported methods to the functions that handle them.
     */
    virtual void InitHandlers() = 0;
    virtual void HandleGet(http_request message) = 0;
    virtual void HandlePut(http_request message) = 0;
    virtual void HandlePost(http_request message) = 0;
    virtual void HandleDelete(http_request message) = 0;
  protected:
    http_listener listener__;
    LoggerInterface& logger__;
    /// The default response to return if the http verb is not implemented.
    static json::value ResponseNotImpl(const http::method& method);
};
}
#endif // CONTROLLER_H
