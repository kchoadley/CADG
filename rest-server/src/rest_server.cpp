// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
#include <iostream>
#include <string>
#include "user_controller.hpp"
#include "data_access_interface.hpp"
#include "data_access_object.hpp"
using cadg_rest::DataAccessInterface;
using cadg_rest::DataAccessObject;
using cadg_rest::UserController;

int main(int argc, const char * argv[]) {
    std::cout << "Starting cadg rest server" << std::endl;
    DataAccessInterface* user_dao = &DataAccessObject::Instance();
    // TODO: Create database and update connection string.
    user_dao->SetConnectionString("Server=myServerAddress;Port=1234;Database=myDataBase;Uid=myUsername;Pwd=myPassword;");
    UserController user_controller(*user_dao);
    std::string server_address;
    if (argc > 2)
        server_address.append(argv[2]);
    else
        server_address.append("http://host_auto_ip4");
    if (argc > 1)
        server_address.append(argv[1]);
    else
        server_address.append(":8080");
    server_address.append("/v1/cadg/api");
    user_controller.endpoint(server_address + "/users");
    try {
        user_controller.Accept().wait();
        std::cout << "Listening for requests at: "
                << user_controller.endpoint() << std::endl;
        std::cout << "Press ENTER to exit." << std::endl;
        std::string line;
        std::getline(std::cin, line);
        user_controller.Shutdown().wait();
    }
    catch(std::exception&  e) {
        std::cerr << "There was an error" << std::endl;
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
