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

    // 90% of data will not be duplicated
    assert(result.size() >= uint8_t(loop * 0.9));
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

    // 30% of data will not be duplicated
    assert(result.size() >= uint8_t(loop * 0.3));
}

}}}}

#endif /* TEST_SCS_FUNCTION_CPP */
