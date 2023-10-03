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
         * val: point of ScsNode object
         */
        std::map<std::string, ScsNode *> nodeMap;

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
         * @return point of ScsNode object
         */
        ScsNode * make_sure_node(const std::string &nodeId);

        /**
         * make sure target itemId exist in itemMap
         * @param p_node point of ScsNode object
         * @param itemId item id
         * @return point of ScsItem object
         */
        ScsItem * make_sure_item(ScsNode *p_node, const std::string &itemId);

        /**
         * make sure target manufacture exist in manufactureMap
         * @param p_node point of ScsNode object
         * @param manuF ScsConfigManufacture object
         * @return point of ScsConfigManufacture object
         */
        ScsConfigManufacture * make_sure_manufacture(ScsNode *p_node, const ScsConfigManufacture &manuF);

        /**
         * split path
         * @param path path, like "(1, 2)"
         * @param leftP left path
         * @param rightP right path
         */
        void splitPath(const std::string &path, std::string &leftP, std::string &rightP);

        /**
         * generate report
         */
        void report();
};


}}

#endif /* SCS_GRAPH_HPP */
