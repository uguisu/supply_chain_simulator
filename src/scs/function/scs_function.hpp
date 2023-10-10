// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef SCS_FUNCTION_HPP
#define SCS_FUNCTION_HPP

#include <string>
#include <random>

namespace scs { namespace func {


// declare function pointer
typedef float (*Fun_ptr)(const int16_t &);

/** item 001 holding cost */
float func_holding_cost_item_001(const int16_t &amount);
/** item 002 holding cost */
float func_holding_cost_item_002(const int16_t &amount);


/**
 * get random generator
 */
std::default_random_engine * getRandomGenerator();

/**
 * Linear
 * 
 * f(x) = ax + b
 */
float func_linear_001(const float &x, const float &a, const float &b);

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

/**
 * uniformly distributed on the closed interval [min, max]
 * 
 * @param min minimum value
 * @param max maximum value
 * @return random integer values as integer
 */
int32_t func_uniform_int_distribution(const int32_t &min, const int32_t &max);

/**
 * poisson distribution
 * 
 * @param occurrence how many times per minute does an event occur on average
 * @return random value
 */
int32_t func_poisson_distribution(const int8_t &occurrence);

}}

#endif /* SCS_FUNCTION_HPP */
