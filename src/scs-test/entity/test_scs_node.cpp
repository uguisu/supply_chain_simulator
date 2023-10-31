// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef TEST_SCS_NODE_CPP
#define TEST_SCS_NODE_CPP

#include <assert.h>
#include <glog/logging.h>

#include "../../scs/function/scs_function.hpp"
#include "../../scs/entity/scs_node.hpp"

#include "test_scs_node.hpp"

namespace scs { namespace test { namespace entity { namespace node {

void test_all()
{
    LOG(INFO) << "Test -> test_scs_node start";

    test_node_001();
    test_edge_001();

    LOG(INFO) << "Test -> test_scs_node end";
}

void generateEdge(scs::entity::ScsEdge &edge)
{
    edge.id = EDGE_ID;
    edge.fromNodeId = FROM_ID;
    edge.toNodeId = TO_ID;
    edge.itemId = ITEM_ID;
    edge.lsFuncId = FUNC_ID_1;
    edge.loFuncId = FUNC_ID_2;
}

void test_node_001()
{
    scs::entity::ScsNode node;
    node.id = ID;
    assert(ID == node.id);
}

void test_edge_001()
{
    scs::entity::ScsEdge edge;
    generateEdge(edge);

    assert(EDGE_ID == edge.id);
    assert(FROM_ID == edge.fromNodeId);
    assert(TO_ID == edge.toNodeId);
    assert(ITEM_ID == edge.itemId);
    assert(FUNC_ID_1 == edge.lsFuncId);
    assert(FUNC_ID_2 == edge.loFuncId);
}

}}}}

#endif /* TEST_SCS_NODE_CPP */
