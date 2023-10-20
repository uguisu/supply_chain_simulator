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
    test_func_normal_distribution_integer_001();
    test_func_uniform_int_distribution_001();
    test_func_poisson_distribution_001();
    test_func_gamma_distribution_001();
    test_func_gamma_distribution_integer_001();

    LOG(INFO) << "Test -> test_scs_function end";
}

void test_func_linear_001()
{
    float x = 123.12;
    float a = 31;
    float b = 0.999;

    float Y = scs::func::func_linear_001(x, a, b);

    assert(Y == (a * x + b));
}

void test_func_normal_distribution_001()
{
    float mean = 5.0;
    float stddev = 2.0;
    
    static uint8_t loop = 20;

    std::unordered_set<float> result;

    for(int i = 0; i < loop; i++)
    {
        result.insert(scs::func::func_normal_distribution(mean, stddev));
    }

    assert(result.size() <= loop);
}

void test_func_normal_distribution_integer_001()
{
    float mean = 5.0;
    float stddev = 2.0;
    
    static uint8_t loop = 20;

    std::unordered_set<int32_t> result;

    for(int i = 0; i < loop; i++)
    {
        result.insert(scs::func::func_normal_distribution_integer(mean, stddev));
    }

    assert(result.size() <= loop);
}

void test_func_uniform_int_distribution_001()
{
    int32_t min = 1;
    int32_t max = 100;
    
    static uint8_t loop = 10;

    std::unordered_set<int32_t> result;

    for(int i = 0; i < loop; i++)
    {
        result.insert(scs::func::func_uniform_int_distribution(min, max));
    }

    assert(result.size() <= loop);
}

void test_func_poisson_distribution_001()
{
    int8_t occurrence = 4;

    static uint8_t loop = 20;

    std::unordered_set<int32_t> result;

    for(int i = 0; i < loop; i++)
    {
        result.insert(scs::func::func_poisson_distribution(occurrence));
    }

    assert(result.size() <= loop);
}

void test_func_gamma_distribution_001()
{
    int8_t alpha = 5;
    int8_t beta = 8;
    
    static uint8_t loop = 20;

    std::unordered_set<float> result;

    for(int i = 0; i < loop; i++)
    {
        result.insert(scs::func::func_gamma_distribution(alpha, beta));
    }

    assert(result.size() <= loop);
}

void test_func_gamma_distribution_integer_001()
{
    int8_t alpha = 5;
    int8_t beta = 8;
    
    static uint8_t loop = 20;

    std::unordered_set<int32_t> result;

    for(int i = 0; i < loop; i++)
    {
        result.insert(scs::func::func_gamma_distribution_integer(alpha, beta));
    }

    assert(result.size() <= loop);
}

}}}}

#endif /* TEST_SCS_FUNCTION_CPP */
