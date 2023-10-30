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
typedef float (*Fun_ptr)(const float &);

// // The holding cost of each material is stored as a function pointer in funcMap
// std::map<std::string, long> funcMap {
//     {
//         "func_linear_001", 
//     }
// };

class AbstractScsFunction
{
    public:
        /** functio name */
        std::string m_name;

        /**
         * calculate
         * @param x input amount
         */
        virtual float cal(const float &x);

        // virtual ~AbstractScsFunction();
    protected:
        /**
         * get random generator
         */
        std::default_random_engine * getRandomGenerator();
};

class ScsFuncLinear001 : public AbstractScsFunction
{
    public:
        /** paramater */
        float m_a = 1;
        /** bias */
        float m_b = 0;

        /**
         * calculate
         * @param x input amount
         */
        virtual float cal(const float &x);

        /**
         * construct
         * @param a paramater
         * @param b bias
         */
        ScsFuncLinear001(const float &a, const float &b);

        /**
         * construct
         */
        ScsFuncLinear001() {};
    
    private:
        /**
         * Linear
         * 
         * f(x) = ax + b
         * 
         * @param x input amount
         * @param a paramater
         * @param b bias
         */
        float ScsFuncLinear001::func_linear_001(const float &x, const float &a = 1, const float &b = 0);
};

class ScsFuncNormalDistribution : public AbstractScsFunction
{
    public:
        /** μ */
        float m_mean = 1;
        /** σ is the Standard deviation */
        float m_stddev = 0;

        /**
         * calculate
         * @param x input amount(will be ignored)
         */
        virtual float cal(const float &x);

        /**
         * construct
         * @param mean μ
         * @param stddev σ is the Standard deviation
         */
        ScsFuncNormalDistribution(const float &mean, const float &stddev);

        /**
         * construct
         */
        ScsFuncNormalDistribution() {};
    
    private:
        /**
         * Normal distribution / Gaussian distribution
         * 
         * @param mean μ
         * @param stddev σ is the Standard deviation
         * @return random value
         */
        float ScsFuncNormalDistribution::func_normal_distribution(const float &mean, const float &stddev);
};

class ScsFuncUniformIntDistribution : public AbstractScsFunction
{
    public:
        /** min */
        int32_t m_min = 1;
        /** max */
        int32_t m_max = 100;

        /**
         * calculate
         * @param x input amount(will be ignored)
         */
        virtual float cal(const float &x);

        /**
         * construct
         * @param min minimum value
         * @param max maximum value
         */
        ScsFuncUniformIntDistribution(const int32_t &min, const int32_t &max);

        /**
         * construct
         */
        ScsFuncUniformIntDistribution() {};
    
    private:
        /**
         * uniformly distributed on the closed interval [min, max]
         * 
         * @param min minimum value
         * @param max maximum value
         * @return random integer values as integer
         */
        int32_t func_uniform_int_distribution(const int32_t &min, const int32_t &max);
};

class ScsFuncPoissonDistribution : public AbstractScsFunction
{
    public:
        /** how many times per minute does an event occur on average */
        int8_t m_occurrence = 1;

        /**
         * calculate
         * @param x input amount(will be ignored)
         */
        virtual float cal(const float &x);

        /**
         * construct
         * @param occurrence how many times per minute does an event occur on average
         */
        ScsFuncPoissonDistribution(const int8_t &occurrence);

        /**
         * construct
         */
        ScsFuncPoissonDistribution() {};
    
    private:
        /**
         * poisson distribution
         * 
         * @param occurrence how many times per minute does an event occur on average
         * @return random value
         */
        int32_t func_poisson_distribution(const int8_t &occurrence);
};

class ScsFuncGammaDistribution : public AbstractScsFunction
{
    public:
        /** alpha */
        int8_t m_alpha = 1;
        /** beta */
        int8_t m_beta = 10;

        /**
         * calculate
         * @param x input amount(will be ignored)
         */
        virtual float cal(const float &x);

        /**
         * construct
         * @param alpha alpha
         * @param beta beta
         */
        ScsFuncGammaDistribution(const int8_t &alpha, const int8_t &beta);

        /**
         * construct
         */
        ScsFuncGammaDistribution() {};
    
    private:
        /**
         * gamma distribution
         * 
         * @param alpha alpha
         * @param beta beta
         * @return random value
         */
        float func_gamma_distribution(const int8_t &alpha, const int8_t &beta);
};

class ScsFuncHoldingCostItem : public AbstractScsFunction
{
    public:
        /** magnification rate */
        float m_rate = 1;

        /**
         * calculate
         * @param x input amount
         */
        virtual float cal(const float &x);

        /**
         * construct
         * @param rate magnification rate
         */
        ScsFuncHoldingCostItem(const float &rate);

        /**
         * construct
         */
        ScsFuncHoldingCostItem() {};
    
    private:
        /**
         * holding cost
         * @param amount item amount
         * @param rate magnification rate
         * @return cost value
         */
        float func_holding_cost_item(const float &amount, const float &rate);
};

}}

#endif /* SCS_FUNCTION_HPP */
