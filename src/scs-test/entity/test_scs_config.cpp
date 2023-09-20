// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef TEST_SCS_CONFIG_CPP
#define TEST_SCS_CONFIG_CPP

#include <glog/logging.h>

#include "../../scs/entity/scs_config.hpp"

#include "test_scs_config.hpp"

namespace scs { namespace test { namespace entity {

void test_001()
{
    scs::entity::ScsConfig config;
    config.setNodeAmount(10);
    LOG(INFO) << "amount: " << config.getNodeAmount();
}

}}}

#endif /* TEST_SCS_CONFIG_CPP */
