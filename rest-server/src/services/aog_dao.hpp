/**
 *  Alert Originator Groups Data Access
 *
 * Copyright 2019   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley, Shawn Hulce, Michael McCulley
 *
 * @file        aog_dao.hpp
 * @authors     Shawn Hulce
 * @date        January 2019
 */
#ifndef REST_SERVER_AOG_DAO_HPP
#define REST_SERVER_AOG_DAO_HPP
#include "aog_dao_interface.hpp"
#include "logger.hpp"
#include "log_level.hpp"
#include <string>
#include <vector>

namespace cadg_rest {

    class AogDao : public AogDaoInterface {

    public:
        /// Instance returns a reference to the DataAccessObject.
        /**
         * Instance implements the Singleton design pattern.
         */
        static AogDao& Instance();
        /// Deletes the copy constructor to enforce singleton.
        AogDao(AogDao const&) = delete;
        /// Deletes the assignment constructor to enforce singleton.
        void operator=(AogDao const&) = delete;

        /// AOG handling methods
        std::optional<std::vector<Aog>> GetAogs() override;
        std::optional<std::vector<Aog>> GetAogByName(std::string name) override;
        std::optional<std::vector<Aog>> GetAogsByAgency(std::string agency) override;
        std::optional<bool> AddAog(Aog aog) override;
        std::optional<std::vector<Aog>> GetAogById(int id) override;
        std::optional<bool> UpdateAog(Aog aog) override;
        std::optional<bool> DeleteAog(int id) override;
        void SetConnectionString(std::string connStr) override;

    private:
        AogDao() { }
        std::string connStr_;
    };

}  // namespace cadg_rest

#endif //REST_SERVER_AOG_DAO_HPP