// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/// A REST endpoint controller implementation class for users.
/**
 * UserController implements the interface defined by Controller.
 * This provides an example of how to use and inject a Data Access Object
 * as well as passing a logger to the base Controller.
 *
 * @file        user_controller.cpp
 * @authors     Kristofer Hoadley
 * @date        November, 2018
 */
#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H
#include <controller.hpp>
#include "data_access_interface.hpp"
using cadg_rest::DataAccessInterface;

namespace cadg_rest {
class UserController: public Controller {
  public: 
    UserController(LoggerInterface& logger__, DataAccessInterface& dao__) : dao__(dao__), Controller(logger__) {
      // dao__.AddUser(User {"Kris Hoadley", 17, "TheBestLikeNoOneEverWas"});
      // dao__.AddUser(User {"Shawn Hulce", 12, "ecluhwordpass!4"});
    }
    ~UserController() { }

    // must make virtual methods non-virtual here
    void InitHandlers() override;
    /**
     * HandleGet will return a user or collection of users determined
     * by the parameters in the url path.
     * If there is not url path, it returns all users.
     * IF there is a user id (a number) next in the path, it returns
     * a user with that id, or no user if there isn't one.
     * If a query for name is in the path, it returns all users with
     * the name as a part of their name.
     * 
     * @param message The http request message to be parsed.
     */
    void HandleGet(http_request message) override;
    /**
     * HandlePut will update a user's data if one exists.
     * The user id should be at the end of the url path.
     * The user's new data should be in the body as json.
     * 
     * @param message The http request message to be parsed.
     */
    void HandlePut(http_request message) override;
    /**
     * HandlePost will add a new user or collection of users to this endpoint.
     * The body should include json of the users to be posted.
     * 
     * @param message The http request message to be parsed.
     */
    void HandlePost(http_request message) override;
    /**
     * HandleDelete will delete a user's data if one exists.
     * The user id should be at the end of the url path.
     * 
     * @param message The http request message to be parsed.
     */
    void HandleDelete(http_request message) override;
    /**
     * GetUserByID wraps the logic for when a GET request specifies a User ID.
     * The response json is passed by reference so it can be updated.
     * 
     * @param resonse The reference to the current response json.
     * @param path The path with the user id in it.
     */
    void GetUserByID(json::value& response, const std::string& path);
    /**
     * GetUsersByName wraps the logic for when a GET request specifies a User Name.
     * The response json is passed by reference so it can be updated.
     * 
     * @param resonse The reference to the current response json.
     * @param user_name The name, or partial name, of the user
     */
    void GetUsersByName(json::value& response, const std::string& user_name);
    /**
     * ParseUserID with extract the ID of a user as a string from the url path.
     * 
     * @param path The path to extract the user id from.
     * @return the string with only the user ID in it.
     */
    std::string ParseUserID(const std::string& path);
  private:
    DataAccessInterface& dao__;
};
}
#endif // USER_CONTROLLER_H
