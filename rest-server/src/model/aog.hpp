//
// Created by shulce on 1/16/19.
//

#ifndef REST_SERVER_AOG_HPP
#define REST_SERVER_AOG_HPP

#endif //REST_SERVER_AOG_HPP

#include <string>
#include "cpprest/json.h"

namespace cadg_rest {

    struct Aog {
        int id;
        std::string name;
        std::string agency;
        web::json::value to_json() {
            auto aog_json = web::json::value::object();
            aog_json["name"] = web::json::value::string(name);
            aog_json["agency"] = web::json::value::string(agency);
            return aog_json;
        }
        //Compares if two Aog constructs are the same
        inline bool operator==(const Aog& other) {
            return id == other.id && name == other.name && agency == other.agency;
        }
    };
}  // namespace cadg_rest
