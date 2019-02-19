/// A DAO for disseminators.
/**
 * This data access object adheres to the DisseminatorDaoInterface. It is a singleton,
 * accessed through the static method Instance().
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 *
 * @file        disseminator_dao.hpp
 * @authors     Michael McCulley, Kristofer Hoadley
 * @date        February, 2019
 */
#ifndef ADMIN_DAO_H
#define ADMIN_DAO_H
#include <string>
#include <vector>
#include "disseminator_dao_interface.hpp"
#include "logger.hpp"
#include "log_level.hpp"

namespace cadg_rest {
/// A DAO for disseminators.
/**
 * DisseminatorDao implements CRUD operations on the disseminator data store.
 */
class DisseminatorDao : public DisseminatorDaoInterface {
  public:
    /// Instance returns a reference to the DisseminatorDao.
    /**
     * Instance implements the Singleton design pattern.
     */
    static DisseminatorDao& Instance();
    /// Deletes the copy constructor to enforce singleton.
    DisseminatorDao(DisseminatorDao const&) = delete;
    /// Deletes the assignment constructor to enforce singleton.
    void operator=(DisseminatorDao const&) = delete;

    bool Requery();
    std::optional<std::vector<Disseminator>> GetDisseminators() override;
    std::optional<std::vector<Disseminator>> GetDisseminatorsByName(const std::string& name) override;
    std::optional<Disseminator> GetDisseminatorByID(int id) override;
    std::optional<bool> RemoveDisseminator(int id) override;
    std::optional<bool> AddDisseminator(Disseminator disseminator) override;
    std::optional<bool> UpdateDisseminator(Disseminator disseminator) override;
    
  private:
    std::string getEnvVar(std::string const& key) {
        char const* val = getenv(key.c_str()); 
        return val == NULL ? std::string() : std::string(val);
    }
    DisseminatorDao();
    std::vector<Disseminator> disseminators__;
    std::string conn_str__;
    std::string db_disseminators_table__;
    LoggerInterface& logger__;
};
}
#endif // ADMIN_DAO_H
