// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef SCS_COST_TYPE_HPP
#define SCS_COST_TYPE_HPP

#include <string>

namespace scs { namespace enums {

/**
 * cost type
 */
enum class CostType
{
    HoldingCost = 1,
    ShortageCost = 2,
    SalvageCost = 3,
    Consumer = 4,
    Order = 5,
    Shipment = 6
};

}}

#endif /* SCS_COST_TYPE_HPP */
