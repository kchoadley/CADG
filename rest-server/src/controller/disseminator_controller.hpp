/// A REST endpoint controller implementation class for disseminators.
/**
 * DisseminatorController implements the interface defined by Controller.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 *
 * @file        disseminator_controller.hpp
 * @authors     Kristofer Hoadley
 * @date        February, 2019
 */
#ifndef DISSEMINATOR_CONTROLLER_H
#define DISSEMINATOR_CONTROLLER_H
#include <controller.hpp>
#include "disseminator_dao_interface.hpp"
using cadg_rest::DisseminatorDaoInterface;

namespace cadg_rest {
class DisseminatorController: public Controller {
  public: 
    DisseminatorController(DisseminatorDaoInterface& dao__) : dao__(dao__) { }
    ~DisseminatorController() { }

    // must make virtual methods non-virtual here
    void InitHandlers() override;
    /// Returns the requested disseminator(s).
    /**
     * HandleGet will return a disseminator or collection of disseminators determined
     * by the parameters in the url path.
     * 
     * '/v1/cadg/api/disseminators/'
     *    GET at root path returns all disseminators.
     * 
     * '/v1/cadg/api/disseminators/{id}'
     *    GET with disseminator id (integer) in the path returns
     *    an disseminator with that id, or no disseminator if there isn't one.
     * 
     * '/v1/cadg/api/disseminators/{id}/password'
     * ```{
     *    "username":"{username}",
     *    "password":"{password}"
     * }```
     *    GET on an id/password will validate a user's password.
     *    The username and password should be passed into the body as a json object.
     *    Success -> 204: 'No Content'
     *    Failure -> 400: 'Bad Request'
     * 
     * '/v1/cadg/api/disseminators?username={username}'
     *    GET with a query for username returns disseminator with that username.
     * 
     * @param message The http request to be parsed.
     */
    void HandleGet(http_request message) override;
    /// Updates a current disseminator's data.
    /**
     * HandlePut will update a disseminator's data if one exists.
     * The disseminator id should be at the end of the url path.
     * The disseminator's new data should be in the body as json.
     * 
     * 
     * '/v1/cadg/api/disseminators/{id}/password'
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
    /// Creates a new disseminator.
    /**
     * HandlePost will add a new disseminator or collection of disseminators to this endpoint.
     * The body should include json of the disseminators to be posted.
     * 
     * @param message The http request message to be parsed.
     */
    void HandlePost(http_request message) override;
    /// Removes an existing disseminator.
    /**
     * HandleDelete will delete a disseminator's data if one exists.
     * The disseminator id should be at the end of the url path.
     * 
     * @param message The http request message to be parsed.
     */
    void HandleDelete(http_request message) override;
  private:
    DisseminatorDaoInterface& dao__;
};
}
#endif // DISSEMINATOR_CONTROLLER_H