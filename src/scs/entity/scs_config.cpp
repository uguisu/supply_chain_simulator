// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef SCS_CONFIG_CPP
#define SCS_CONFIG_CPP

#include <string>

#include "scs_config.hpp"

namespace scs { namespace entity {

    /**
     * getNodeAmount
     */
    int16_t ScsConfig::getNodeAmount()
    {
        return this->node_amount;
    }

    /**
     * setNodeAmount
     * @param node_amount total node amount
     */
    void ScsConfig::setNodeAmount(const int16_t &node_amount)
    {
        this->node_amount = node_amount;
    }

    ScsConfig::~ScsConfig()
    {}
}}

#endif /* SCS_CONFIG_CPP */