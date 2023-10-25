// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef SCS_PURCHASE_DEMAND_CPP
#define SCS_PURCHASE_DEMAND_CPP

#include <string>
#include <vector>

#include "scs_purchase_demand.hpp"

namespace scs { namespace entity {

    /**
     * setup value
     */
    void ScsPurchaseDemand::from_json(const json &jsonObject)
    {
        for(auto &demand : jsonObject[FIELD_PURCHASE])
        {
            ScsNodePurchaseDemand snpd;
            snpd.from_json(demand);
            this->purchase.push_back(snpd);
        }
    }

    /**
     * setup value
     */
    void ScsNodePurchaseDemand::from_json(const json &jsonObject)
    {
        jsonObject.at(FIELD_NODE_ID).get_to(this->nodeId);

        for(auto &demand : jsonObject[FIELD_DEMANDS])
        {
            ScsNodeItemPurchaseDemand snipd;
            snipd.from_json(demand);
            this->demands.push_back(snipd);
        }
    }

    /**
     * setup value
     */
    void ScsNodeItemPurchaseDemand::from_json(const json &jsonObject)
    {
        jsonObject.at(FIELD_ITEM_ID).get_to(this->itemId);
        jsonObject.at(FIELD_AMOUNT).get_to(this->amount);
    }
}}

#endif /* SCS_PURCHASE_DEMAND_CPP */
