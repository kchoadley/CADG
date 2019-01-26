/**
 * Interface for Alert Originator Groups Data Access
 *
 * Copyright 2019   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley, Shawn Hulce, Michael McCulley
 *
 * @file        aog_dao_interface.hpp
 * @authors     Shawn Hulce
 * @date        January 2019
 */

#ifndef REST_SERVER_AOG_DAO_INTERFACE_HPP
#define REST_SERVER_AOG_DAO_INTERFACE_HPP
#include "aog.hpp"
#include <string>
#include <vector>
#include <optional>

namespace cadg_rest {

    class AogDaoInterface {

    public:

        virtual std::optional<std::vector<Aog>> GetAogs() = 0;

        virtual std::optional<std::vector<Aog>> GetAogByName(std::string name) = 0;

        virtual std::optional<std::vector<Aog>> GetAogsByAgency(std::string agency) = 0;

        virtual std::optional<bool> AddAog(Aog aog) = 0;

        virtual std::optional<std::vector<Aog>> GetAogById(int id) = 0;

        virtual std::optional<bool> UpdateAog(Aog aog) = 0;

        virtual std::optional<bool> DeleteAog(int id) = 0;

        virtual void SetConnectionString(std::string connStr) = 0;
    };

} //end cadg_rest

#endif //REST_SERVER_AOG_DAO_INTERFACE_HPP