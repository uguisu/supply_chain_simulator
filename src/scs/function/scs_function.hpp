// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef SCS_FUNCTION_HPP
#define SCS_FUNCTION_HPP

#include <string>
// #include <vector>
// #include <map>

namespace scs { namespace func {


// declare function pointer
typedef float (*Fun_ptr)(const int16_t &);

/** item 001 holding cost */
float func_holding_cost_item_001(const int16_t &amount);
/** item 002 holding cost */
float func_holding_cost_item_002(const int16_t &amount);


/**
 * Linear
 * 
 * f(x) = ax + b
 */
float func_linear_001(const float &x, const float &a = 1, const float &b = 0);

/**
 * Normal distribution / Gaussian distribution
 * 
 * @param mean μ
 * @param stddev σ is the Standard deviation
 * @return random value
 */
float func_normal_distribution(const float &mean, const float &stddev);

/**
 * Normal distribution / Gaussian distribution
 * 
 * @param mean μ
 * @param stddev σ is the Standard deviation
 * @return random integer value
 */
int32_t func_normal_distribution_integer(const float &mean, const float &stddev);

}}

#endif /* SCS_FUNCTION_HPP */
