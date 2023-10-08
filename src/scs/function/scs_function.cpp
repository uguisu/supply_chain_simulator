// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef SCS_FUNCTION_CPP
#define SCS_FUNCTION_CPP

#include <string>

namespace scs { namespace func {

    /** item 001 holding cost */
    float func_holding_cost_item_001(const int16_t &amount)
    {
        return amount * 2;
    }

    /** item 002 holding cost */
    float func_holding_cost_item_002(const int16_t &amount)
    {
        return amount * 0.5;
    }


/**
 * Linear
 * 
 * f(x) = ax + b
 * 
 * @param x input amount
 * @param a paramater
 * @param b bias
 */
float func_linear_001(const float &x, const float &a = 1, const float &b = 0)
{
    return a * x + b;
}

}}

#endif /* SCS_FUNCTION_CPP */
