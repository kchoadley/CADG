//
// Created by shulce on 1/19/19.
//

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

        virtual void AddAog(Aog aog) = 0;

        virtual void SetConnectionString(std::string connStr) = 0;
    };

} //end cadg_rest

#endif //REST_SERVER_AOG_DAO_INTERFACE_HPP