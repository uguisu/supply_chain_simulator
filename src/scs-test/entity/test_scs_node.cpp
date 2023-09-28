// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef TEST_SCS_NODE_CPP
#define TEST_SCS_NODE_CPP

#include <assert.h>
#include <glog/logging.h>

#include "../../scs/core/scs_function.hpp"
#include "../../scs/entity/scs_node.hpp"

#include "test_scs_node.hpp"

namespace scs { namespace test { namespace entity { namespace node {

void test_all()
{
    LOG(INFO) << "Test -> test_scs_node start";

    test_node_001();
    test_edge_001();
    
    test_901();
    test_902();

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

void test_901()
{
    // declare ScsNode object
    scs::entity::ScsNode node;

    // store functions
    std::string name1 = "item1";
    node.getFuncMap().insert(std::make_pair(name1, &scs::core::func_holding_cost_item_001));

    std::string name2 = "item2";
    node.getFuncMap().insert(std::make_pair(name2, &scs::core::func_holding_cost_item_002));

    // check result
    assert(scs::core::func_holding_cost_item_002(6) == node.execFunc(name2, 6));
    assert(2 == node.getFuncMap().size());
}

/**
 * test exception
 */
void test_902()
{
    // declare ScsNode object
    scs::entity::ScsNode node;

    // store functions
    std::string name1 = "item1";
    node.getFuncMap().insert(std::make_pair(name1, &scs::core::func_holding_cost_item_001));

    std::string name2 = "no item";

    bool isThrow = false;

    try
    {
        node.execFunc(name2, 6);
    }
    catch(const std::exception &e)
    {
        isThrow = true;
    }
    
    assert(isThrow);
}

}}}}

#endif /* TEST_SCS_NODE_CPP */
