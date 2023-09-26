// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef SCS_ITEM_HPP
#define SCS_ITEM_HPP

#include <string>
#include <unordered_set>
#include <map>

#include "../enums/scs_cost_type.hpp"

namespace scs { namespace entity {

class ScsItem
{
    public:
        /**
         * id
         */
        std::string id;
    
        /**
         * function map
         * 
         * key: CostType
         * val: function id set
         */
        std::map<scs::enums::CostType, std::unordered_set<std::string>> functionMap;

        /**
         * remainder
         */
        float remainder = 0.0;
};

}}

#endif /* SCS_ITEM_HPP */
