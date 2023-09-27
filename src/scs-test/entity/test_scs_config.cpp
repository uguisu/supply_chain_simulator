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

    assert(2 == config.lo[0].funcList.size());
    assert("(1, 2)" == config.lo[0].path);
    assert("A" == config.lo[0].funcList[0].itemId);
    assert("func1" == config.lo[0].funcList[0].funcId);
    assert("B" == config.lo[0].funcList[1].itemId);
    assert("func2" == config.lo[0].funcList[1].funcId);

    assert(2 == config.ls[0].funcList.size());
    assert("(3, 4)" == config.ls[0].path);
    assert("C" == config.ls[0].funcList[0].itemId);
    assert("func3" == config.ls[0].funcList[0].funcId);
    assert("D" == config.ls[0].funcList[1].itemId);
    assert("func4" == config.ls[0].funcList[1].funcId);

    assert("5" == config.formula[0].nodeId);
    assert(1 == config.formula[0].manufacture.size());
    assert("E" == config.formula[0].manufacture[0].itemId);
    assert(float(2.1) == config.formula[0].manufacture[0].processTime);
    assert(2 == config.formula[0].manufacture[0].componentList.size());
    assert("F" == config.formula[0].manufacture[0].componentList[0].itemId);
    assert(float(3.2) == config.formula[0].manufacture[0].componentList[0].materials);
    assert("G" == config.formula[0].manufacture[0].componentList[1].itemId);
    assert(float(10.9) == config.formula[0].manufacture[0].componentList[1].materials);

    assert("(5, 6)" == config.edges[0].path);
    assert(2 == config.edges[0].items.size());
    assert("H" == config.edges[0].items[0]);
    assert("I" == config.edges[0].items[1]);
    assert("(7, 8)" == config.edges[1].path);
    assert(1 == config.edges[1].items.size());
    assert("J" == config.edges[1].items[0]);
}

}}}}

#endif /* TEST_SCS_CONFIG_CPP */
