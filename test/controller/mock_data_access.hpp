///GMock of the Data Access Interface
/**
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 *
 * @file    mock_data_access.cpp
 * @authors Vaniya Agrawal
 * @date    January, 2019
 */

#ifndef CADG_MOCK_DATA_ACCESS_INTERFACE_HPP
#define CADG_MOCK_DATA_ACCESS_INTERFACE_HPP
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include "user.hpp"
#include "data_access_interface.hpp"
using namespace std;

namespace cadg_rest{
class MockDataAccess : public DataAccessInterface {
public:
    MOCK_METHOD0(GetUsers, std::optional<std::vector<User>>());
    MOCK_METHOD1(GetUsersByName, std::optional<std::vector<User>>(const std::string& name));
    MOCK_METHOD1(GetUserByID, std::optional<std::vector<User>>(int id));
    MOCK_METHOD1(RemoveUser, std::optional<bool>(int id));
    MOCK_METHOD1(AddUser, std::optional<bool>(User user));
    MOCK_METHOD2(UpdateUser, std::optional<bool>(int id, web::json::object user_info));
    MOCK_METHOD1(SetConnectionString, std::optional<bool>(std::string connStr));
};
}
#endif //CADG_MOCK_DATA_ACCESS_INTERFACE_HPP
