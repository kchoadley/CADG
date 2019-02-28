// Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
//                  Shawn Hulce, Michael McCulley
/// Functions for validating CAP Alert Messages.
/**
* This is the implemenation file for functions required to validate CAP Alert Messages.
 *
 * @file        cap_validation.hpp
 * @authors     Michael McCulley
 * @date        February, 2019
 */

#ifndef CAP_VALIDATION_H
#define CAP_VALIDATION_H
#include <logger.hpp>
#include <logger_interface.hpp>
#include "log_level.hpp"
#include "../gSoapFiles/CAP/soapH.h"
#include <time.h>
#include <regex>

namespace cap_validation {

    static std::string time_t_to_xml_dt_string(const time_t &time);

    static void string_to_vector(std::string s, const std::string &delimiter, std::vector<std::string> &elems);

    static std::vector<std::string> parse_double_quoted_then_spaces(std::string s);

    static bool validate_addresses(std::string addresses);

    static bool validate_references(std::string references);

    static bool validate_circle_string(const std::string &circle_string);

    static bool validate_coordinate_pair_string(const std::string &coordinate_pair);

    static bool validate_soap_alert_info_resource(const _ns2__alert_info_resource resource);

    static bool validate_soap_alert_info_area(const _ns2__alert_info_area area);

    static bool validate_soap_alert_info(const _ns2__alert_info info);

    static bool validate_soap_alert(const _ns2__alert &alert);
}
#endif //CAP_VALIDATION_H