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

    std::string targetNodeID = "n_1";
    std::string targetItemID = "A";

    // declare ScsConfig object
    scs::entity::ScsConfig config;

    std::string testJsonFile = "../docs/config_example_case_001.json";

    config.read(testJsonFile);

    scs::entity::ScsGraph graph;
    graph.build(config);

    assert(1 == graph.nodeMap.count(targetNodeID));
    assert(1 == (*graph.nodeMap[targetNodeID]).itemMap.count(targetItemID));
}

void test_002()
{
    std::string targetNodeID_1 = "n_1";
    std::string targetNodeID_2 = "n_2";
    std::string targetNodeID_3 = "n_3";
    std::string targetNodeID_4 = "n_4";
    std::string targetItemID_A = "A";
    std::string targetItemID_B = "B";
    std::string targetItemID_C = "C";

    // declare ScsConfig object
    scs::entity::ScsConfig config;

    std::string testJsonFile = "../docs/config_example_case_002.json";

    config.read(testJsonFile);

    scs::entity::ScsGraph graph;
    graph.build(config);

    // show report
    LOG(INFO) << graph.report();

    // declare work variable
    scs::entity::ScsNode *wrk_node;

    assert(1 == graph.nodeMap.count(targetNodeID_1));
    wrk_node = graph.nodeMap[targetNodeID_1];
    assert(1 == (*wrk_node).itemMap.count(targetItemID_A));
    assert(0 == (*wrk_node).manufactureMap.count(targetItemID_A));
    assert(10 == (*wrk_node).itemMap[targetItemID_A]->quantity);

    assert(1 == graph.nodeMap.count(targetNodeID_2));
    wrk_node = graph.nodeMap[targetNodeID_2];
    assert(1 == (*wrk_node).itemMap.count(targetItemID_B));
    assert(0 == (*wrk_node).manufactureMap.count(targetItemID_B));
    assert(11 == (*wrk_node).itemMap[targetItemID_B]->quantity);

    assert(1 == graph.nodeMap.count(targetNodeID_3));
    wrk_node = graph.nodeMap[targetNodeID_3];
    assert(3 == (*wrk_node).itemMap.size());
    assert(1 == (*wrk_node).itemMap.count(targetItemID_A));
    assert(1 == (*wrk_node).itemMap.count(targetItemID_B));
    assert(1 == (*wrk_node).itemMap.count(targetItemID_C));
    assert(1 == (*wrk_node).manufactureMap.count(targetItemID_C));
    assert(12 == (*wrk_node).itemMap[targetItemID_A]->quantity);
    assert(13 == (*wrk_node).itemMap[targetItemID_B]->quantity);
    assert(14 == (*wrk_node).itemMap[targetItemID_C]->quantity);

    assert(1 == graph.nodeMap.count(targetNodeID_4));
    wrk_node = graph.nodeMap[targetNodeID_4];
    assert(1 == (*wrk_node).itemMap.count(targetItemID_C));
    assert(0 == (*wrk_node).manufactureMap.count(targetItemID_C));
    assert(15 == (*wrk_node).itemMap[targetItemID_C]->quantity);
}

}}}}

#endif /* TEST_SCS_GRAPH_CPP */
