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
#include "logger_interface.hpp"
using namespace web;
using namespace http;
using namespace http::experimental::listener;

namespace cadg_rest {
class Controller {
  public: 
    Controller(LoggerInterface& logger__) : logger__(logger__) { }
    ~Controller() { }

    void endpoint(const std::string& endpoint);
    std::string endpoint() const;
    pplx::task<void> Accept();
    pplx::task<void> Shutdown();
    static std::map<std::string, std::string> Queries(std::string query_string);

    virtual void InitHandlers() = 0;
    virtual void HandleGet(http_request message) = 0;
    virtual void HandlePut(http_request message) = 0;
    virtual void HandlePost(http_request message) = 0;
    virtual void HandleDelete(http_request message) = 0;
  protected:
    http_listener listener__;
    LoggerInterface& logger__;
    static json::value ResponseNotImpl(const http::method& method);
};
}
#endif // CONTROLLER_H
