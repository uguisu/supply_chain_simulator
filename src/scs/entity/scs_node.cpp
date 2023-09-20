// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef SCS_NODE_CPP
#define SCS_NODE_CPP

#include <string>
#include <vector>

#include <glog/logging.h>

#include "scs_node.hpp"

namespace scs { namespace entity {

    float func_holding_cost_item_001(const int16_t &amount)
    {
        return amount * 2;
    }
    float func_holding_cost_item_002(const int16_t &amount)
    {
        return amount * 5;
    }

    /**
     * set name
     */
    void ScsNode::setName(const std::string &name)
    {
        this->name = name;
    }
    /**
     * get name
     */
    std::string ScsNode::getName()
    {
        return this->name;
    }

    /**
     * set input edge list
     */
    void ScsNode::setInputEdgeList(const std::vector<ScsEdge> &inputEdgeList)
    {
        this->inputEdgeList = inputEdgeList;
    }
    /**
     * get input edge list
     */
    std::vector<ScsEdge> ScsNode::getInputEdgeList()
    {
        return this->inputEdgeList;
    }

    /**
     * set output edge list
     */
    void ScsNode::setOutputEdgeList(const std::vector<ScsEdge> &outputEdgeList)
    {
        this->outputEdgeList = outputEdgeList;
    }   
    /**
     * get output edge list
     */
    std::vector<ScsEdge> ScsNode::getOutputEdgeList()
    {
        return this->outputEdgeList;
    }


    std::map<std::string, ScsNode::Fun_ptr>& ScsNode::getFuncMap()
    {
        return this->funcMap;
    }
    float ScsNode::execFunc(const std::string &funcName, const int16_t &val)
    {
        float rtn = 0.0;

        if(this->funcMap.count(funcName))
        {
            rtn = (*(this->funcMap[funcName]))(val);
        } else {
            rtn = -999.99;
        }

        return rtn;
    }




    ScsNode::~ScsNode()
    {}

    /**
     * set name
     */
    void ScsEdge::setName(const std::string &name)
    {
        this->name = name;
    }
    /**
     * get name
     */
    std::string ScsEdge::getName()
    {
        return this->name;
    }

    /**
     * set input node list
     */
    void ScsEdge::setInputNodeList(const std::vector<ScsNode> &inputNodeList)
    {
        this->inputNodeList = inputNodeList;
    }
    /**
     * get input node list
     */
    std::vector<ScsNode> ScsEdge::getInputNodeList()
    {
        return this->inputNodeList;
    }

    /**
     * set output node list
     */
    void ScsEdge::setOutputNodeList(const std::vector<ScsNode> &outputNodeList)
    {
        this->outputNodeList = outputNodeList;
    }
    /**
     * get output node list
     */
    std::vector<ScsNode> ScsEdge::getOutputNodeList()
    {
        return this->outputNodeList;
    }

    ScsEdge::~ScsEdge()
    {}
}}

#endif /* SCS_NODE_CPP */
