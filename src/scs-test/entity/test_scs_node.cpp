// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef TEST_SCS_NODE_CPP
#define TEST_SCS_NODE_CPP

#include <assert.h>

#include "../../scs/core/scs_function.hpp"
#include "../../scs/entity/scs_node.hpp"

#include "test_scs_node.hpp"

namespace scs { namespace test { namespace entity { namespace node {

void test_all()
{
    test_001();
    test_002();
}

void test_001()
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
void test_002()
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
