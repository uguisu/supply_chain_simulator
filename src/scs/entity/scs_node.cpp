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

    /**
     * get function map
     */
    std::map<std::string, scs::core::Fun_ptr>& ScsNode::getFuncMap()
    {
        return this->funcMap;
    }
    /**
     * execute target function
     */
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
    {
        // delete point map "manufactureMap"
        for(auto wrk_pair : this->manufactureMap)
        {
            delete wrk_pair.second;
        }
        
        // delete point map "itemMap"
        for(auto wrk_pair : this->itemMap)
        {
            delete wrk_pair.second;
        }
    }

    ScsEdge::~ScsEdge()
    {}
}}

#endif /* SCS_NODE_CPP */
