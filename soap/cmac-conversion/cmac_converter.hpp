//
// Created by Ross on 1/18/2019.
//

#include <iostream>
#include <string>
#include "../pugixml-1.9/src/pugixml.hpp"
#include "../pugixml-1.9/src/pugixml.cpp"

#ifndef CADG_REST_SERVER_CMAC_CONVERTER_H
#define CADG_REST_SERVER_CMAC_CONVERTER_H
class CMAC {
public:
    static void convert(std::string soap_filename, std::string cmac_filename);
};
#endif //CADG_REST_SERVER_CMAC_CONVERTER_H
