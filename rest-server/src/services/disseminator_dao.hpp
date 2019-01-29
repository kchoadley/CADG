// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/// A DAO for disseminators.
/**
 * This data access object adheres to the DisseminatorDaoInterface. It is a singleton,
 * accessed through the static method Instance().
 *
 * @file        disseminator_dao.hpp
 * @authors     Michael McCulley
 * @date        January, 2019
 */
#ifndef ADMIN_DAO_H
#define ADMIN_DAO_H
#include <string>
#include <vector>
#include "disseminator.hpp"
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

    bool Requery() override;
    std::vector<Disseminator> GetDisseminators() override;
    std::vector<Disseminator> GetDisseminatorsByName(const std::string& name) override;
    std::vector<Disseminator> GetDisseminatorByID(int id) override;
    bool RemoveDisseminator(int id) override;
    bool AddDisseminator(Disseminator disseminator) override;
    bool UpdateDisseminator(Disseminator disseminator) override;
    
  private:
    std::string getEnvVar(std::string const& key) {
        char const* val = getenv(key.c_str()); 
        return val == NULL ? std::string() : std::string(val);
    }
    DisseminatorDao();
    std::vector<Disseminator> disseminators__;
    std::string conn_str__;
    LoggerInterface& logger;
};
}
#endif // ADMIN_DAO_H
