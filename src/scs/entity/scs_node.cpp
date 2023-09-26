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

    std::map<std::string, scs::core::Fun_ptr>& ScsNode::getFuncMap()
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
            throw std::runtime_error("Can not find target function by name.");
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
