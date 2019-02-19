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
    /**
     * AogDaoInterface is an interface class to be implemented for interfacing with the database storing
     * Aog information. Handles CRUD operations on the database.
     */
    class AogDaoInterface {

    public:

        /**
         * GetAogs returns all Originators stored in the database;
         * @return Vector of all Aog's or nullopt if none found or error
         */
        virtual std::optional<std::vector<Aog>> GetAogs() = 0;
        /**
         * GetAogByName returns all Originators with similar names to the input string
         * @param name String input name to search for
         * @return Vector of Aog's matching input or nullopt if none found or error
         */
        virtual std::optional<std::vector<Aog>> GetAogByName(std::string name) = 0;
        /**
         * GetAogsByAgency returns all Originators with agency matching input string
         * @param agency String input agency to search for
         * @return Vector of Aog's matching input or nullopt if none found or error
         */
        virtual std::optional<std::vector<Aog>> GetAogsByAgency(std::string agency) = 0;
        /**
         * AddAog adds a new Originator to the database
         * @param aog Aog data structure input containing the name and agency
         * @return Boolean true if successful, false if failed. Nullopt if database connection fails
         */
        virtual std::optional<bool> AddAog(Aog aog) = 0;
        /**
         * GetAogById gets the Aog with the matching input ID if it exists
         * @param id integer value of the id to find
         * @return Vector with single Aog if found, nullopt if not
         */
        virtual std::optional<std::vector<Aog>> GetAogById(int id) = 0;
        /**
         * Updates the data in the database for the given Aog
         * @param aog Valid aog structure with corresponding database entry
         * @return true if successful, false on failure, and nullopt on database connection failure
         */
        virtual std::optional<bool> UpdateAog(Aog aog) = 0;
        /**
         * Deletes the Aog with input id
         * @param id integer value id of Aog for deletion
         * @return bool true on success, false on failure, nullopt on database connection failure
         */
        virtual std::optional<bool> DeleteAog(int id) = 0;
        /**
         * Deprecated method that can be utilized to set the nanodbc connection string for the Dao
         * @param connStr string value for database connection
         */
        virtual void SetConnectionString(std::string connStr) = 0;
    };

} //end cadg_rest

#endif //REST_SERVER_AOG_DAO_INTERFACE_HPP