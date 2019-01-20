//
// Created by shulce on 1/19/19.
//

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
        std::vector<Aog> GetAogs() override;
        std::vector<Aog> GetAogByName(std::string name) override;
        std::vector<Aog> GetAogsByAgency(std::string agency) override;
        void AddAog(Aog aog) override;
        void SetConnectionString(std::string connStr) override;

    private:
        AogDao() { }
        std::string connStr_;
    };

}

#endif //REST_SERVER_AOG_DAO_HPP