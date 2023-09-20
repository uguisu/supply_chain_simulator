// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef SCS_NODE_HPP
#define SCS_NODE_HPP

#include <string>
#include <vector>

namespace scs { namespace entity {

class ScsNode;
class ScsEdge;

/// TODO 假设每个仓库存储容量无限大


/*
Basic Structure:
    ┌──────────────────┐
    │       Node       │
    ├──────────────────┤
    │ name             │
    │ inputEdgeList    │
    │ outputEdgeList   │
    └──────────────────┘
             │
    ┌──────────────────┐
    │       Edge       │
    ├──────────────────┤
    │ name             │
    │ inputNodeList    │
    │ outputNodeList   │
    └──────────────────┘
             │
    ┌──────────────────┐
    │       Node       │
    ├──────────────────┤
    │ name             │
    │ inputEdgeList    │
    │ outputEdgeList   │
    └──────────────────┘
 */

/**
 * Node
 */
class ScsNode
{
    public:
        /**
         * set name
         */
        void setName(const std::string &name);
        /**
         * get name
         */
        std::string getName();

        /**
         * set input edge list
        */
        void setInputEdgeList(const std::vector<ScsEdge> &inputEdgeList);
        /**
         * get input edge list
        */
        std::vector<ScsEdge> getInputEdgeList();

        /**
         * set output edge list
        */
        void setOutputEdgeList(const std::vector<ScsEdge> &outputEdgeList);
        /**
         * get output edge list
        */
        std::vector<ScsEdge> getOutputEdgeList();

        ~ScsNode();
    private:
        /** node name */
        std::string name = "";

        /** input edge list */
        std::vector<ScsEdge> inputEdgeList;
        /** output edge list */
        std::vector<ScsEdge> outputEdgeList;

        // TODO 每种物料的持有成本

};

class ScsEdge
{

    public:
        /**
         * set name
         */
        void setName(const std::string &name);
        /**
         * get name
         */
        std::string getName();

        /**
         * set input node list
        */
        void setInputNodeList(const std::vector<ScsNode> &inputNodeList);
        /**
         * get input node list
        */
        std::vector<ScsNode> getInputNodeList();

        /**
         * set output node list
        */
        void setOutputNodeList(const std::vector<ScsNode> &outputNodeList);
        /**
         * get output node list
        */
        std::vector<ScsNode> getOutputNodeList();

        ~ScsEdge();
    private:
        /** node name */
        std::string name = "";

        /** input node list */
        std::vector<ScsNode> inputNodeList;
        /** output node list */
        std::vector<ScsNode> outputNodeList;

        // TODO 每种物料的运输都有成本
};

}}

#endif /* SCS_NODE_HPP */