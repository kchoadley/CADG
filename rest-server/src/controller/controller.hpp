// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <map>
#include <string>
#include <vector>
#include <cpprest/http_listener.h>
#include <cpprest/http_msg.h>
#include <pplx/pplxtasks.h>
<<<<<<< fd91337dfaecc0701fecb2a15d05a0353768652a
#include "logger_interface.hpp"
=======
>>>>>>> PR Review modifications. Minor adjustments
using namespace web;
using namespace http;
using namespace http::experimental::listener;

<<<<<<< fd91337dfaecc0701fecb2a15d05a0353768652a
namespace cadg_rest {
class Controller {
  public: 
    Controller(LoggerInterface& logger__) : logger__(logger__) { }
    ~Controller() { }
=======
namespace aoi_rest {
class Controller {
  public: 
    Controller();
    ~Controller();
>>>>>>> PR Review modifications. Minor adjustments

    void endpoint(const std::string& endpoint);
    std::string endpoint() const;
    pplx::task<void> Accept();
    pplx::task<void> Shutdown();
<<<<<<< fd91337dfaecc0701fecb2a15d05a0353768652a
    static std::map<std::string, std::string> Queries(std::string query_string);
=======
    std::vector<std::string> RequestPath(const http_request& message);
    std::map<std::string, std::string> Queries(std::string query_string);
>>>>>>> PR Review modifications. Minor adjustments

    virtual void InitHandlers() = 0;
    virtual void HandleGet(http_request message) = 0;
    virtual void HandlePut(http_request message) = 0;
    virtual void HandlePost(http_request message) = 0;
    virtual void HandleDelete(http_request message) = 0;
  protected:
    http_listener listener__;
<<<<<<< fd91337dfaecc0701fecb2a15d05a0353768652a
    LoggerInterface& logger__;
=======
>>>>>>> PR Review modifications. Minor adjustments
    static json::value ResponseNotImpl(const http::method& method);
};
}
#endif // CONTROLLER_H
