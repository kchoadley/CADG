// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H
#include <controller.hpp>
#include "data_access_interface.hpp"
using cadg_rest::DataAccessInterface;

namespace cadg_rest {
class UserController: public Controller {
  public: 
    UserController(DataAccessInterface& dao__) : dao__(dao__), Controller() {
      //dao__.AddUser(User {"Kris Hoadley", 17, "TheBestLikeNoOneEverWas"});
      //dao__.AddUser(User {"Shawn Hulce", 12, "ecluhwordpass!4"});
    }
    ~UserController() { }

    // must make virtual methods non-virtual here
    void InitHandlers() override;
    void HandleGet(http_request message) override;
    void HandlePut(http_request message) override;
    void HandlePost(http_request message) override;
    void HandleDelete(http_request message) override;
    void GetUserByID(json::value& response, const std::string& path);
    void GetUsersByName(json::value& response, const std::string& user_name);
    std::string ParseUserID(const std::string& path);
  private:
    DataAccessInterface& dao__;
};
}
#endif // USER_CONTROLLER_H
