// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef SCS_FUNCTION_HPP
#define SCS_FUNCTION_HPP

#include <string>
#include <vector>
#include <map>

namespace scs { namespace core {


// declare function pointer
typedef float (*Fun_ptr)(const int16_t &);

/** item 001 holding cost */
float func_holding_cost_item_001(const int16_t &amount);
/** item 002 holding cost */
float func_holding_cost_item_002(const int16_t &amount);


}}

#endif /* SCS_FUNCTION_HPP */
