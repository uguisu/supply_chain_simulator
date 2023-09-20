// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef TEST_SCS_NODE_HPP
#define TEST_SCS_NODE_HPP

#include <assert.h>

#include "../../scs/entity/scs_node.hpp"

#include "test_scs_node.hpp"

namespace scs { namespace test { namespace entity { namespace node {

void test_001()
{
    // declare ScsNode object
    scs::entity::ScsNode node;

    // store functions
    std::string name1 = "func1";
    node.getFuncMap().insert(std::make_pair(name1, &scs::entity::func_holding_cost_item_001));

    std::string name2 = "func2";
    node.getFuncMap().insert(std::make_pair(name2, &scs::entity::func_holding_cost_item_002));

    // check result
    assert(scs::entity::func_holding_cost_item_002(6) == node.execFunc(name2, 6));
    assert(2 == node.getFuncMap().size());
}

}}}}

#endif /* TEST_SCS_NODE_HPP */
