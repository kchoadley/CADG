/// A REST endpoint controller implementation class for admins.
/**
 * AdminController implements the interface defined by Controller.
 * This provides an example of how to use and inject a Data Access Object
 * as well as passing a logger to the base Controller.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 *
 * @file        admin_controller.hpp
 * @authors     Kristofer Hoadley
 * @date        January, 2019
 */
#ifndef ADMIN_CONTROLLER_H
#define ADMIN_CONTROLLER_H
#include <controller.hpp>
#include "admin_dao_interface.hpp"
using cadg_rest::AdminDaoInterface;

namespace cadg_rest {
class AdminController: public Controller {
  public: 
    AdminController(AdminDaoInterface& dao__) : dao__(dao__) { }
    ~AdminController() { }

    // must make virtual methods non-virtual here
    void InitHandlers() override;
    /// Returns the requested admin(s).
    /**
     * HandleGet will return a admin or collection of admins determined
     * by the parameters in the url path.
     * 
     * '/v1/cadg/api/admins/'
     *    GET at root path returns all admins.
     * 
     * '/v1/cadg/api/admins/{id}'
     *    GET with admin id (integer) in the path returns
     *    an admin with that id, or no admin if there isn't one.
     * 
     * '/v1/cadg/api/admins/{id}/password'
     * ```{
     *    "username":"{username}",
     *    "password":"{password}"
     * }```
     *    GET on an id/password will validate a user's password.
     *    The username and password should be passed into the body as a json object.
     *    Success -> 204: 'No Content'
     *    Failure -> 400: 'Bad Request'
     * 
     * '/v1/cadg/api/admins?username={username}'
     *    GET with a query for username returns admin with that username.
     * 
     * @param message The http request to be parsed.
     */
    void HandleGet(http_request message) override;
    /// Updates a current admin's data.
    /**
     * HandlePut will update a admin's data if one exists.
     * The admin id should be at the end of the url path.
     * The admin's new data should be in the body as json.
     * 
     * 
     * '/v1/cadg/api/admins/{id}/password'
     * ```{
     *    "password":"{password}"
     * }```
     *    PUT on an id/password will update user's password.
     *    The password should be passed into the body as a json object.
     *    Success -> 204: 'No Content'
     *    Failure -> 400: 'Bad Request'
     * 
     * @param message The http request message to be parsed.
     */
    void HandlePut(http_request message) override;
    /// Creates a new admin.
    /**
     * HandlePost will add a new admin or collection of admins to this endpoint.
     * The body should include json of the admins to be posted.
     * 
     * @param message The http request message to be parsed.
     */
    void HandlePost(http_request message) override;
    /// Removes an existing admin.
    /**
     * HandleDelete will delete a admin's data if one exists.
     * The admin id should be at the end of the url path.
     * 
     * @param message The http request message to be parsed.
     */
    void HandleDelete(http_request message) override;
    /// Returns an existing admin with the specified ID.
    /**
     * GetAdminByID wraps the logic for when a GET request specifies a Admin ID.
     * The response json is passed by reference so it can be updated.
     * 
     * @param response The reference to the current response json.
     * @param path The path with the admin id in it.
     */
    bool GetAdminByID(json::value& response, const std::string& path);
    /**
     * GetAdminsByName wraps the logic for when a GET request specifies a Admin Name.
     * The response json is passed by reference so it can be updated.
     * 
     * @param response The reference to the current response json.
     * @param admin_name The name, or partial name, of the admin
     */
    bool GetAdminsByUsername(json::value& response, const std::string& username);
  private:
    AdminDaoInterface& dao__;
};
}
#endif // ADMIN_CONTROLLER_H
