///Mocks the CADG Data Access Object (Users) for testing purposes
/**
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 *
 * @file    mock_data_access.hpp
 * @authors Vaniya Agrawal
 * @date    January, 2019
 */
#include "user.hpp"
#include "data_access_interface.hpp"
#include <optional>
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

      std::optional<std::vector<User>> GetUsers() override { return users__; };
      std::optional<std::vector<User>> GetUsersByName(const std::string& name) override { return users__; };
      std::optional<std::vector<User>> GetUserByID(int id) override { return users__; };
      std::optional<bool> RemoveUser(int id) override { return true; };
      std::optional<bool> AddUser(User user) override { return true; };
      std::optional<bool> UpdateUser(int id, web::json::object user_info) override { return true; };
    private:
      std::vector<User> users__;
  };
}
