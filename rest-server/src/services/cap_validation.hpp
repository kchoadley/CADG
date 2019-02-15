// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/// Functions for validating CAP Alert Messages.
/**
 * This class contains functions for validating CAP Alert Messages.
 *
 * @file        cap_validation.hpp
 * @authors     Michael McCulley
 * @date        February, 2019
 */

#ifndef CAP_VALIDATION_H
#define CAP_VALIDATION_H
#include <optional>
#include <logger.hpp>
#include <logger_interface.hpp>
#include "log_level.hpp"
#include "../gSoapFiles/CAP/soapH.h"

namespace cap_validation {
    static bool from_soap_alert(_ns2__alert &soap_alert) {
        try {
            auto &logger(cadg_rest::Logger::Instance());
            // Validate required fields.

            // Validate conditional fields.

            // Validate format of all fields.
            return true;
        } catch (...) {
            return false;
        }
};
}
#endif //CAP_VALIDATION_H