// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#ifndef DATA_ACCESS_INTERFACE_H
#define DATA_ACCESS_INTERFACE_H
#include <string>
#include <vector>
#include "user.hpp"

namespace cadg_rest {
class DataAccessInterface {
  public:
    virtual std::vector<User> GetUsers() = 0;
    virtual std::vector<User> GetUsersByName(const std::string& name) = 0;
    virtual std::vector<User> GetUserByID(int id) = 0;
    virtual bool RemoveUser(User user) = 0;
    virtual void AddUser(User user) = 0;
    virtual void SetConnectionString(std::string connStr) = 0;
};
}
#endif // DATA_ACCESS_INTERFACE_H
