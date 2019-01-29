// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/// An interface for an Disseminator DAO.
/**
 * This defines the interface for a data access object (DAO) which is
 * used to provide CRUD operations on a data storage of Alert Disseminators.
 *
 * @file        disseminator_dao_interface.hpp
 * @authors     Michael McCulley
 * @date        January, 2019
 */
#ifndef DISSEMINATOR_DAO_INTERFACE_H
#define DISSEMINATOR_DAO_INTERFACE_H
#include <string>
#include <vector>
#include "disseminator.hpp"

namespace cadg_rest {
/**
 * DataAccessInterface defines several CRUD operations for a disseminator data store.
 * This interface must be defines in an inheriting class.
 */
class DisseminatorDaoInterface {
  public:
    /**
     * GetDisseminators gets all disseminators in the data store.
     * 
     * @return Vector of all disseminators.
     */
    virtual std::vector<Disseminator> GetDisseminators() = 0;
    /**
     * GetDisseminatorsByName gets all disseminators in the data store which have a name that
     * partially or fully matches the name argument.
     * 
     * @param name The name of the disseminator(s) to search for.
     * @return Vector of all disseminators that match the name.
     */
    virtual std::vector<Disseminator> GetDisseminatorsByName(const std::string& name) = 0;
    /**
     * GetDisseminatorByID gets the disseminator in the data store by id.
     * 
     * @param id The id of the disseminator to return.
     * @return Vector containing the found disseminator, or empty if there is no matching disseminator.
     */
    virtual std::vector<Disseminator> GetDisseminatorByID(int id) = 0;
    /**
     * RemoveDisseminator removes the disseminator in the data store by id.
     * 
     * @param id The id of the disseminator to remove.
     * @return Bool indicating successful removal.
     */
    virtual bool RemoveDisseminator(int id) = 0;
    /**
     * AddDisseminator adds the disseminator to the data store.
     * 
     * @param disseminator The disseminator to add to the data store.
     */
    virtual bool AddDisseminator(Disseminator disseminator) = 0;
    /**
     * UpdateDisseminator updates a disseminator in the data store.
     * 
     * @param id The id of the disseminator to update.
     * @param disseminator_info The updated information for the disseminator.
     */
    virtual bool UpdateDisseminator(Disseminator disseminator) = 0;
};
}
#endif // DISSEMINATOR_DAO_INTERFACE_H
