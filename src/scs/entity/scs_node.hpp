// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef SCS_NODE_HPP
#define SCS_NODE_HPP

#include <string>
#include <vector>
#include <map>

#include "../core/scs_function.hpp"
#include "scs_config.hpp"
#include "scs_item.hpp"

namespace scs { namespace entity {

class ScsNode;
class ScsEdge;

/// TODO 假设每个仓库存储容量无限大

/*
Basic Structure:
    ┌──────────────────┐
    │       Node       │
    ├──────────────────┤
    │ id               │
    │ inputEdgeList    │
    │ outputEdgeList   │
    │ manufactureMap   │
    │ itemMap          │
    └──────────────────┘
             │
    ┌──────────────────┐
    │       Edge       │
    ├──────────────────┤
    │ id               │
    │ inputNodeList    │
    │ outputNodeList   │
    └──────────────────┘
             │
    ┌──────────────────┐
    │       Node       │
    ├──────────────────┤
    │ id               │
    │ inputEdgeList    │
    │ outputEdgeList   │
    │ manufactureMap   │
    │ itemMap          │
    └──────────────────┘
 */

/**
 * Node
 */
class ScsNode
{
    public:

        /**
         * node id
         */
        std::string id = "";

        /**
         * input edge list
         */
        std::vector<ScsEdge> inputEdgeList;

        /**
         * output edge list
         */
        std::vector<ScsEdge> outputEdgeList;

        /**
         * manufacture map
         * 
         * key: item_id
         * val: ScsConfigManufacture object
         */
        std::map<std::string, ScsConfigManufacture> manufactureMap;

        /**
         * items that stored in local node
         */
        std::map<std::string, ScsItem> itemMap;



        // TODO 这里仅仅是一个demo
        /**
         * get function map
         */
        std::map<std::string, scs::core::Fun_ptr>& getFuncMap();
        /**
         * execute target function
         */
        float execFunc(const std::string &funcName, const int16_t &val);

        ~ScsNode();
    private:

        // The holding cost of each material is stored as a function pointer in funcMap
        std::map<std::string, scs::core::Fun_ptr> funcMap;
};

class ScsEdge
{

    public:

        /**
         * node id
         */
        std::string id = "";

        /** input node list */
        std::vector<ScsNode> inputNodeList;
        /** output node list */
        std::vector<ScsNode> outputNodeList;

        ~ScsEdge();
    private:

        // TODO 每种物料的运输都有成本

};

}}

#endif /* SCS_NODE_HPP */
