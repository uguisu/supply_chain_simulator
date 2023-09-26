// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef TEST_SCS_CONFIG_CPP
#define TEST_SCS_CONFIG_CPP

#include <string>
#include <assert.h>
#include <glog/logging.h>

#include "../../scs/entity/scs_config.hpp"

#include "test_scs_config.hpp"

namespace scs { namespace test { namespace entity { namespace config {


void test_all()
{
    LOG(INFO) << "Test -> test_scs_config start";

    test_001();

    LOG(INFO) << "Test -> test_scs_config end";
}

void test_001()
{
    // // declare ScsConfig object
    scs::entity::ScsConfig config;

    std::string testJsonFile = "../docs/config_example.json";

    config.read(testJsonFile);

    assert(1 == config.lo.size());
    assert(1 == config.ls.size());
    assert(1 == config.formula.size());
    assert(2 == config.edges.size());
    assert(2 == config.holdingCost.size());
    assert(2 == config.shortageCost.size());
    assert(2 == config.salvageCost.size());
    assert(2 == config.consumer.size());
}

}}}}

#endif /* TEST_SCS_CONFIG_CPP */
