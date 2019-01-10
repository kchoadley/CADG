///Mocks the CADG Data Access Object (Users) for testing purposes
/**
 * (License)
 * @file    mock_data_access.hpp
 * @authors { Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley, Shawn Hulce, Michael McCulley }
 * @date    1/9/2019
 */
#include "user.hpp"
#include "data_access_interface.hpp"
#include <string>
#include <vector>

namespace cadg_rest{
  class MockDataAccess : public DataAccessInterface {
    public:
      MockDataAccess() {
        User vaniya = {"Vaniya", 1, "myPassword"};
        User ross = {"Ross", 2, "RossPassword"};
        User shawn = {"Shawn", 3, "anotherPass"};
        User kris = {"Kris", 4, "PW"};
        User mike = {"Michael", 5, "password123"};
        users__.push_back(vaniya);
        users__.push_back(ross);
        users__.push_back(shawn);
        users__.push_back(kris);
        users__.push_back(mike);
      };
      MockDataAccess(MockDataAccess const&) = delete;
      void operator=(MockDataAccess const&) = delete;

      std::vector<User> GetUsers() override { return users__; };
      std::vector<User> GetUsersByName(const std::string& name) override { return users__; };
      std::vector<User> GetUserByID(int id) override { return users__; };
      bool RemoveUser(User user) override { return true; };
      void AddUser(User user) override { };
      void UpdateUser(int id, web::json::object user_info) override { };
      void SetConnectionString(std::string connStr) override { };
    private:
      std::vector<User> users__;
  };
}
