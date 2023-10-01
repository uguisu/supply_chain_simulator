// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef SCS_GRAPH_HPP
#define SCS_GRAPH_HPP

#include <string>
#include <vector>
#include <map>

#include "../enums/scs_cost_type.hpp"
#include "scs_config.hpp"
#include "scs_node.hpp"


namespace scs { namespace entity {

class ScsGraph
{
    public:
    
        /**
         * node map
         * 
         * key: node id
         * val: ScsNode object
         */
        std::map<std::string, ScsNode> nodeMap;

        /**
         * build graph via config
         * @param config ScsConfig object
         */
        void build(const scs::entity::ScsConfig &config);

        ~ScsGraph() {};
    
    private:

        /**
         * varify graph structure
         */
        void verify();

        /**
         * process LO/LS
         * @param lols ScsConfigLoLs object
         * @param costType CostType
         */
        void _processLoLs(const std::vector<ScsConfigLoLs> &lols, const scs::enums::CostType &costType);

        /**
         * process formula
         * @param formula ScsConfigFormula list
         */
        void _processFormula(const std::vector<ScsConfigFormula> &formula);

        /**
         * process edge
         * @param edge ScsConfigEdge list
         */
        void _processEdge(const std::vector<ScsConfigEdge> &edge);

        /**
         * process cost
         * @param cost ScsConfigCost list
         * @param costType CostType
         */
        void _processCost(const std::vector<ScsConfigCost> &cost, const scs::enums::CostType &costType);

        /**
         * make sure target nodeId exist in nodeMap
         * @param nodeId node id
         * @return ScsNode object
         */
        // TODO use void
        const ScsNode & make_sure_node(const std::string &nodeId);

        /**
         * make sure target itemId exist in itemMap
         * @param nodeId node id
         * @param itemId item id
         */
        // TODO use void
        const ScsItem & make_sure_item(const std::string &nodeId, const std::string &itemId);

        /**
         * split path
         * @param path path, like "(1, 2)"
         * @param leftP left path
         * @param rightP right path
         */
        void splitPath(const std::string &path, std::string &leftP, std::string &rightP);
};


}}

#endif /* SCS_GRAPH_HPP */
