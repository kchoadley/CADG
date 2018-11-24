// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#ifndef DATA_ACCESS_OBJECT_H
#define DATA_ACCESS_OBJECT_H
#include <string>
#include <vector>
#include "user.hpp"
#include "data_access_interface.hpp"

namespace cadg_rest {
class DataAccessObject : public DataAccessInterface {
  public:
    static DataAccessObject& Instance();
    DataAccessObject(DataAccessObject const&) = delete;
    void operator=(DataAccessObject const&) = delete;

    std::vector<User> GetUsers() override;
    std::vector<User> GetUsersByName(const std::string& name) override;
    std::vector<User> GetUserByID(int id) override;
    bool RemoveUser(User user) override;
    void AddUser(User user) override;
    void UpdateUser(int id, web::json::object user_info) override;
    void SetConnectionString(std::string connStr) override;
  private:
    DataAccessObject() { }
    std::vector<User> users__;
    std::string connStr_;
};
}
#endif // DATA_ACCESS_OBJECT_H
