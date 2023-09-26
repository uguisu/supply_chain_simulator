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
         * build graph via config
         * @param config ScsConfig object
         */
        void build(const scs::entity::ScsConfig &config);

        ~ScsGraph() {};
    
    private:

        /**
         * node map
         * 
         * key: node id
         * val: ScsNode object
         */
        std::map<std::string, ScsNode> nodeMap;

        /**
         * varify graph structure
         */
        void verify();

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
         * @param node ScsNode object
         */
        void make_sure_node(const std::string &nodeId, ScsNode &node);

        /**
         * make sure target itemId exist in itemMap
         * @param itemMap item map
         * @param itemId item id
         * @param item ScsItem object
         */
        void make_sure_item(
            std::map<std::string, ScsItem> &itemMap,
            const std::string &itemId,
            const ScsItem &item);

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
