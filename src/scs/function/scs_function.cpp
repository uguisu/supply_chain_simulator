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
#include <stdexcept>

#include "scs_function.hpp"

namespace scs { namespace func {

    /**
     * get random generator
     */
    std::default_random_engine * AbstractScsFunction::getRandomGenerator()
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
     * calculate
     * @param x input amount
     */
    float ScsFuncLinear001::cal(const float &x)
    {
        return this->func_linear_001(x, this->m_a, this->m_b);
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
    float ScsFuncLinear001::func_linear_001(const float &x, const float &a, const float &b)
    {
        return a * x + b;
    }

    /**
     * construct
     * @param a paramater
     * @param b bias
     */
    ScsFuncLinear001::ScsFuncLinear001(const float &a, const float &b)
    {
        this->m_a = a;
        this->m_b = b;
    }

    // register
    REFLECT(Linear001);

    /**
     * Normal distribution / Gaussian distribution
     * 
     * @param mean μ
     * @param stddev σ is the Standard deviation
     * @return random value
     */
    float ScsFuncNormalDistribution::func_normal_distribution(const float &mean, const float &stddev)
    {
        // declare normal distribution object
        std::normal_distribution<double> distribution(mean, stddev);
        // get generator
        std::default_random_engine * generator = this->getRandomGenerator();
        // generate result
        float rtn = distribution(*generator);
        // delete point
        delete generator;

        return rtn;
    }

    /**
     * calculate
     * @param x input amount(will be ignored)
     */
    float ScsFuncNormalDistribution::cal(const float &x)
    {
        return this->func_normal_distribution(this->m_mean, this->m_stddev);
    }

    /**
     * construct
     * @param mean μ
     * @param stddev σ is the Standard deviation
     */
    ScsFuncNormalDistribution::ScsFuncNormalDistribution(const float &mean, const float &stddev)
    {
        this->m_mean = mean;
        this->m_stddev = stddev;
    }

    // register
    REFLECT(NormalDistribution);

    /**
     * uniformly distributed on the closed interval [min, max]
     * 
     * @param min minimum value
     * @param max maximum value
     * @return random integer values as integer
     */
    int32_t ScsFuncUniformIntDistribution::func_uniform_int_distribution(const int32_t &min, const int32_t &max)
    {
        // get generator
        std::default_random_engine * generator = this->getRandomGenerator();
        // declare function
        std::uniform_int_distribution<int32_t> distribution(min, max);

        // generate result
        int32_t rtn = distribution(*generator);
        // delete point
        delete generator;

        return rtn;
    }

    /**
     * calculate
     * @param x input amount(will be ignored)
     */
    float ScsFuncUniformIntDistribution::cal(const float &x)
    {
        return this->func_uniform_int_distribution(this->m_min, this->m_max);
    }

    /**
     * construct
     * @param min minimum value
     * @param max maximum value
     */
    ScsFuncUniformIntDistribution::ScsFuncUniformIntDistribution(const int32_t &min, const int32_t &max)
    {
        this->m_min = min;
        this->m_max = max;
    }

    // register
    REFLECT(UniformIntDistribution);

    /**
     * poisson distribution
     * 
     * @param occurrence how many times per minute does an event occur on average
     * @return random value
     */
    int32_t ScsFuncPoissonDistribution::func_poisson_distribution(const int8_t &occurrence)
    {
        // get generator
        std::default_random_engine * generator = this->getRandomGenerator();
        // declare function
        std::poisson_distribution<int32_t> distribution(occurrence);

        // generate result
        int32_t rtn = distribution(*generator);
        // delete point
        delete generator;

        return rtn;
    }

    /**
     * calculate
     * @param x input amount(will be ignored)
     */
    float ScsFuncPoissonDistribution::cal(const float &x)
    {
        return this->func_poisson_distribution(this->m_occurrence);
    }

    /**
     * construct
     * @param occurrence how many times per minute does an event occur on average
     */
    ScsFuncPoissonDistribution::ScsFuncPoissonDistribution(const int8_t &occurrence)
    {
        this->m_occurrence = occurrence;
    }

    // register
    REFLECT(PoissonDistribution);

    /**
     * gamma distribution
     * 
     * @param alpha alpha
     * @param beta beta
     * @return random value
     */
    float ScsFuncGammaDistribution::func_gamma_distribution(const int8_t &alpha, const int8_t &beta)
    {
        // declare normal distribution object
        std::gamma_distribution<double> distribution(alpha, beta);
        // get generator
        std::default_random_engine * generator = this->getRandomGenerator();
        // generate result
        float rtn = distribution(*generator);
        // delete point
        delete generator;

        return rtn;
    }

    /**
     * calculate
     * @param x input amount(will be ignored)
     */
    float ScsFuncGammaDistribution::cal(const float &x)
    {
        return this->func_gamma_distribution(this->m_alpha, this->m_beta);
    }

    /**
     * construct
     * @param alpha alpha
     * @param beta beta
     */
    ScsFuncGammaDistribution::ScsFuncGammaDistribution(const int8_t &alpha, const int8_t &beta)
    {
        this->m_alpha = alpha;
        this->m_beta = beta;
    }

    // register
    REFLECT(GammaDistribution);

    /**
     * holding cost
     * @param amount item amount
     * @param rate magnification rate
     * @return cost value
     */
    float ScsFuncHoldingCostItem::func_holding_cost_item(const float &amount, const float &rate)
    {
        return amount * rate;
    }

    /**
     * calculate
     * @param x input amount(will be ignored)
     */
    float ScsFuncHoldingCostItem::cal(const float &x)
    {
        return this->func_holding_cost_item(x, this->m_rate);
    }

    /**
     * construct
     * @param rate magnification rate
     */
    ScsFuncHoldingCostItem::ScsFuncHoldingCostItem(const float &rate)
    {
        this->m_rate = rate;
    }

    // register
    REFLECT(HoldingCostItem);

    ScsReflector::~ScsReflector()
    {
        // delete point map "m_factory"
        for(auto wrk_pair : this->m_factory)
        {
            delete wrk_pair.second;
        }

        this->m_factory.clear();
    }

    /**
     * register
     * @param funcName function name
     * @param funcF instance creator
     */
    void ScsReflector::registerFactory(const std::string &funcName, ScsFunctionFactory *funcF)
    {
        // verify
        if(this->m_factory.find(funcName) != this->m_factory.end())
        {
            // avoid duplicate declare
            throw std::runtime_error("Can not find target function by name.");
        }

        this->m_factory.insert(std::make_pair(funcName, funcF));

    }

    /**
     * get instance
     * @param funcName function name
     * @return instance pointer
     */
    AbstractScsFunction * ScsReflector::getNewInstance(const std::string &funcName)
    {
        return this->m_factory.at(funcName)->getNewInstance();
    }

    ScsReflector & reflector()
    {
        static ScsReflector reflector;
        return reflector;
    }
}}

#endif /* SCS_FUNCTION_CPP */
