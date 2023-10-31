// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef TEST_SCS_NODE_HPP
#define TEST_SCS_NODE_HPP

#include <string>

namespace scs { namespace test { namespace entity { namespace node {

const std::string ID = "my_id";
const std::string EDGE_ID = "my_edge_id";
const std::string FROM_ID = "from_id";
const std::string TO_ID = "to_id";
const std::string ITEM_ID = "item_id";
const std::string FUNC_ID_1 = "func_id_1";
const std::string FUNC_ID_2 = "func_id_2";

void test_all();

void test_node_001();
void test_edge_001();

}}}}

#endif /* TEST_SCS_NODE_HPP */
