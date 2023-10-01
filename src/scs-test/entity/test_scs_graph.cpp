// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef TEST_SCS_GRAPH_CPP
#define TEST_SCS_GRAPH_CPP

#include <string>
#include <assert.h>
#include <glog/logging.h>

#include "../../scs/entity/scs_config.hpp"
#include "../../scs/entity/scs_graph.hpp"
#include "test_scs_graph.hpp"

namespace scs { namespace test { namespace entity { namespace graph {

void test_all()
{

    LOG(INFO) << "Test -> test_scs_graph start";

    test_001();
    test_002();

    LOG(INFO) << "Test -> test_scs_graph end";

}

void test_001()
{
    // declare ScsConfig object
    scs::entity::ScsConfig config;

    std::string testJsonFile = "../docs/config_example_case_001.json";

    config.read(testJsonFile);

    scs::entity::ScsGraph graph;
    graph.build(config);

    assert(1 == graph.nodeMap.count("n_1"));
}

void test_002()
{

}

}}}}

#endif /* TEST_SCS_GRAPH_CPP */
