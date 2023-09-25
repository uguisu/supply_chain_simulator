// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef SCS_MAIN_CPP
#define SCS_MAIN_CPP

#include <iostream>

#include "../entity/scs_config.hpp"
#include "../entity/scs_graph.hpp"
#include "scs_main.hpp"


namespace scs { namespace core {

/**
 * build graph
 * @param jsonFileWithPath config file with path
 */
void build_graph(const std::string &jsonFileWithPath)
{
    // read config info from json file
    scs::entity::ScsConfig config;
    config.read(jsonFileWithPath);

    // build graph
    scs::entity::ScsGraph graph;
    graph.build(config);

    // TODO next step ===============
}

}}

#endif /* SCS_MAIN_CPP */
