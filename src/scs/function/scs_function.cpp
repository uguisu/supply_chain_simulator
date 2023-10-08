// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef SCS_FUNCTION_CPP
#define SCS_FUNCTION_CPP

#include <string>
#include <random>
#include <chrono>
#include <stdio.h>

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

/**
 * Normal distribution / Gaussian distribution
 * 
 * @param mean μ
 * @param stddev σ is the Standard deviation
 * @return random value
 */
float func_normal_distribution(const float &mean, const float &stddev)
{
    // "std::random_device" may not work under windows, so in case user use windows, use "std::chrono" instead
    #ifdef _WIN32
        // Create random engine with the help of seed
        unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count(); 
        // declare a generator with above seed
        std::default_random_engine generator(seed);
    #else
        // use system random device
        std::random_device rd;
        // declare a generator with above device
        std::default_random_engine generator(rd());
    #endif

    // declare normal distribution object
    std::normal_distribution<double> distribution(mean, stddev);

    return distribution(generator);
}

/**
 * Normal distribution / Gaussian distribution
 * 
 * @param mean μ
 * @param stddev σ is the Standard deviation
 * @return random integer value
 */
int32_t func_normal_distribution_integer(const float &mean, const float &stddev)
{
    return std::round(func_normal_distribution(mean, stddev));
}

}}

#endif /* SCS_FUNCTION_CPP */
