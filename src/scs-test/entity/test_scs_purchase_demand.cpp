// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef TEST_SCS_PURCHASE_DEMAND_CPP
#define TEST_SCS_PURCHASE_DEMAND_CPP

#include <assert.h>
#include <string>
#include <fstream>
#include <glog/logging.h>

#include "../../scs/entity/scs_purchase_demand.hpp"

#include "test_scs_purchase_demand.hpp"

namespace scs { namespace test { namespace entity { namespace purchase_demand {

void test_all()
{
    LOG(INFO) << "Test -> test_scs_purchase_demand start";

    test_001();

    LOG(INFO) << "Test -> test_scs_purchase_demand end";
}

void test_001()
{
    // declare test json file
    std::string testJsonFile = "../docs/purchase_demand_example.json";

    std::ifstream f(testJsonFile);
    // convert to json object
    json jsonObject = json::parse(f);

    // declare ScsPurchaseDemand object
    scs::entity::ScsPurchaseDemand purchaseDemand;

    // assign value
    purchaseDemand.from_json(jsonObject);

    assert(2 == purchaseDemand.purchase.size());

    assert("1" == purchaseDemand.purchase[0].nodeId);
    assert(2 == purchaseDemand.purchase[0].demands.size());
    assert("A" == purchaseDemand.purchase[0].demands[0].itemId);
    assert(3 == purchaseDemand.purchase[0].demands[0].amount);
    assert("B" == purchaseDemand.purchase[0].demands[1].itemId);
    assert(4 == purchaseDemand.purchase[0].demands[1].amount);

    assert("2" == purchaseDemand.purchase[1].nodeId);
    assert(1 == purchaseDemand.purchase[1].demands.size());
    assert("C" == purchaseDemand.purchase[1].demands[0].itemId);
    assert(88 == purchaseDemand.purchase[1].demands[0].amount);
}

}}}}

#endif /* TEST_SCS_PURCHASE_DEMAND_CPP */
