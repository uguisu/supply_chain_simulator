// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef SCS_NODE_CPP
#define SCS_NODE_CPP

#include <string>

#include "scs_node.hpp"

namespace scs { namespace entity {

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
