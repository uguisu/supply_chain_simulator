// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef SCS_PURCHASE_DEMAND_HPP
#define SCS_PURCHASE_DEMAND_HPP

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace scs { namespace entity {

// declare field name
const std::string FIELD_ITEM_ID = "item_id";
const std::string FIELD_AMOUNT = "amount";
const std::string FIELD_NODE_ID = "node_id";
const std::string FIELD_DEMANDS = "demands";
const std::string FIELD_PURCHASE = "purchase";

// pre-declare class
class ScsPurchaseDemand;
class ScsNodePurchaseDemand;
class ScsNodeItemPurchaseDemand;

/**
 * Purchase Demand
 */
class ScsPurchaseDemand
{
    public:
        /** purchase */
        std::vector<ScsNodePurchaseDemand> purchase;

        /**
         * setup value
         */
        void from_json(const json &jsonObject);

        ~ScsPurchaseDemand() {};
};

/**
 * Purchase Demand for each node
 */
class ScsNodePurchaseDemand
{
    public:
        /** node id */
        std::string nodeId;
        /** demands list */
        std::vector<ScsNodeItemPurchaseDemand> demands;

        /**
         * setup value
         */
        void from_json(const json &jsonObject);

        ~ScsNodePurchaseDemand() {};
};

/**
 * Purchase Demand for each item in node
 */
class ScsNodeItemPurchaseDemand
{
    public:
        /** item id */
        std::string itemId;
        /** amount */
        float amount;

        /**
         * setup value
         */
        void from_json(const json &jsonObject);

        ~ScsNodeItemPurchaseDemand() {};
};

}}

#endif /* SCS_PURCHASE_DEMAND_HPP */
