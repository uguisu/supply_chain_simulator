// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef TEST_SCS_FUNCTION_CPP
#define TEST_SCS_FUNCTION_CPP

#include <assert.h>
#include <glog/logging.h>

#include "../../scs/function/scs_function.hpp"
#include "test_scs_function.hpp"

namespace scs { namespace test { namespace function { namespace func {

void test_all()
{
    LOG(INFO) << "Test -> test_scs_function start";

    test_func_linear_001();

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

}}}}

#endif /* TEST_SCS_FUNCTION_CPP */
