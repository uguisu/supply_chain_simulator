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


#include "scs_function.hpp"

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
 * get random generator
 */
std::default_random_engine * getRandomGenerator()
{
    // "std::random_device" may not work under windows, so in case user use windows, use "std::chrono" instead
    #ifdef _WIN32
        // Create random engine with the help of seed
        unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count(); 
        // declare a generator with above seed
        std::default_random_engine * generator = new std::default_random_engine(seed);
    #else
        // use system random device
        std::random_device rd;
        // declare a generator with above device
        // std::default_random_engine generator(rd());
        std::default_random_engine * generator = new std::default_random_engine(rd());
    #endif

    return generator;
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
    // declare normal distribution object
    std::normal_distribution<double> distribution(mean, stddev);
    // get generator
    std::default_random_engine * generator = getRandomGenerator();
    // generate result
    float rtn = distribution(*generator);
    // delete point
    delete generator;

    return rtn;
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

/**
 * uniformly distributed on the closed interval [min, max]
 * 
 * @param min minimum value
 * @param max maximum value
 * @return random integer values as integer
 */
int32_t func_uniform_int_distribution(const int32_t &min, const int32_t &max)
{
    // get generator
    std::default_random_engine * generator = getRandomGenerator();
    // declare function
    std::uniform_int_distribution<int32_t> distribution(min, max);

    // generate result
    int32_t rtn = distribution(*generator);
    // delete point
    delete generator;

    return rtn;
}

/**
 * poisson distribution
 * 
 * @param occurrence how many times per minute does an event occur on average
 * @return random value
 */
int32_t func_poisson_distribution(const int8_t &occurrence)
{
    // get generator
    std::default_random_engine * generator = getRandomGenerator();
    // declare function
    std::poisson_distribution<int32_t> distribution(occurrence);

    // generate result
    int32_t rtn = distribution(*generator);
    // delete point
    delete generator;

    return rtn;
}

/**
 * gamma distribution
 * 
 * @param alpha alpha
 * @param beta beta
 * @return random value
 */
float func_gamma_distribution(const int8_t &alpha, const int8_t &beta)
{
    // declare normal distribution object
    std::gamma_distribution<double> distribution(alpha, beta);
    // get generator
    std::default_random_engine * generator = getRandomGenerator();
    // generate result
    float rtn = distribution(*generator);
    // delete point
    delete generator;

    return rtn;
}

/**
 * gamma distribution
 * 
 * @param alpha alpha
 * @param beta beta
 * @return random value
 */
int32_t func_gamma_distribution_integer(const int8_t &alpha, const int8_t &beta)
{
    return std::round(func_gamma_distribution(alpha, beta));
}

}}

#endif /* SCS_FUNCTION_CPP */
