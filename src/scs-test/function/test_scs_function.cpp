// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef TEST_SCS_FUNCTION_CPP
#define TEST_SCS_FUNCTION_CPP

#include <assert.h>
#include <glog/logging.h>
#include <unordered_set>

#include "../../scs/function/scs_function.hpp"
#include "test_scs_function.hpp"

namespace scs { namespace test { namespace function { namespace func {

void test_all()
{
    LOG(INFO) << "Test -> test_scs_function start";

    test_func_linear_001();
    test_func_normal_distribution_001();
    test_func_uniform_int_distribution_001();
    test_func_poisson_distribution_001();
    test_func_gamma_distribution_001();

    LOG(INFO) << "Test -> test_scs_function end";
}

void test_func_linear_001()
{
    float x = 123.12;
    float a = 31;
    float b = 0.999;

    scs::func::ScsFuncLinear001 *p_func_linear_001 =
        scs::func::getNewInstance<scs::func::ScsFuncLinear001>("Linear001");
    (*p_func_linear_001).m_a = a;
    (*p_func_linear_001).m_b = b;

    float Y = (*p_func_linear_001).cal(x);

    assert(Y == (a * x + b));
}

void test_func_normal_distribution_001()
{
    float mean = 5.0;
    float stddev = 2.0;
    
    static uint8_t loop = 20;

    std::unordered_set<float> result;

    scs::func::ScsFuncNormalDistribution *p_func_normal_distribution =
        scs::func::getNewInstance<scs::func::ScsFuncNormalDistribution>("NormalDistribution");
    (*p_func_normal_distribution).m_mean = mean;
    (*p_func_normal_distribution).m_stddev = stddev;

    for(int i = 0; i < loop; i++)
    {
        result.insert((*p_func_normal_distribution).cal(-1));
    }

    assert(result.size() <= loop);
}

void test_func_uniform_int_distribution_001()
{
    int32_t min = 1;
    int32_t max = 100;
    
    static uint8_t loop = 10;

    std::unordered_set<int32_t> result;

    scs::func::ScsFuncUniformIntDistribution *p_func_uniform_int_distribution =
        scs::func::getNewInstance<scs::func::ScsFuncUniformIntDistribution>("UniformIntDistribution");
    (*p_func_uniform_int_distribution).m_min = min;
    (*p_func_uniform_int_distribution).m_max = max;

    for(int i = 0; i < loop; i++)
    {
        result.insert((*p_func_uniform_int_distribution).cal(-1));
    }

    assert(result.size() <= loop);
}

void test_func_poisson_distribution_001()
{
    int8_t occurrence = 4;

    static uint8_t loop = 20;

    std::unordered_set<int32_t> result;

    scs::func::ScsFuncPoissonDistribution *p_func_poisson_distribution =
        scs::func::getNewInstance<scs::func::ScsFuncPoissonDistribution>("PoissonDistribution");
    (*p_func_poisson_distribution).m_occurrence = occurrence;

    for(int i = 0; i < loop; i++)
    {
        result.insert((*p_func_poisson_distribution).cal(-1));
    }

    assert(result.size() <= loop);
}

void test_func_gamma_distribution_001()
{
    int8_t alpha = 5;
    int8_t beta = 8;
    
    static uint8_t loop = 20;

    std::unordered_set<float> result;

    scs::func::ScsFuncGammaDistribution *p_func_gamma_distribution =
        scs::func::getNewInstance<scs::func::ScsFuncGammaDistribution>("GammaDistribution");
    (*p_func_gamma_distribution).m_alpha = alpha;
    (*p_func_gamma_distribution).m_beta = beta;

    for(int i = 0; i < loop; i++)
    {
        result.insert((*p_func_gamma_distribution).cal(-1));
    }

    assert(result.size() <= loop);
}


}}}}

#endif /* TEST_SCS_FUNCTION_CPP */
