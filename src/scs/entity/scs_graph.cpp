// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef SCS_GRAPH_CPP
#define SCS_GRAPH_CPP

#include <string>
#include <vector>
#include <sstream>
#include <unordered_set>

#include "scs_config.hpp"
#include "scs_node.hpp"
#include "scs_graph.hpp"


namespace scs { namespace entity {

/**
 * build graph via config
 * @param config ScsConfig object
 */
void ScsGraph::build(const scs::entity::ScsConfig &config)
{
    // go through each config unit, re-build the data structure

    // Field: lo

    // Field: ls

    // Field: formula
    this->_processFormula(config.formula);

    // Field: edge
    this->_processEdge(config.edges);

    // Field: holding_cost
    this->_processCost(config.holdingCost, scs::enums::CostType::HoldingCost);

    // Field: shortage_cost
    this->_processCost(config.shortageCost, scs::enums::CostType::ShortageCost);

    // Field: salvage_cost
    this->_processCost(config.salvageCost, scs::enums::CostType::SalvageCost);

    // Field: consumer
    this->_processCost(config.consumer, scs::enums::CostType::Consumer);

}

/**
 * process formula
 * @param formula ScsConfigFormula list
 */
void ScsGraph::_processFormula(const std::vector<ScsConfigFormula> &formula)
{
    for(ScsConfigFormula scsFormula : formula)
    {
        // fetch all nodes from formula declaration
        ScsNode _node;
        this->make_sure_node(scsFormula.nodeId, _node);

        // fetch all manufacture
        for(ScsConfigManufacture scsManufacture : scsFormula.manufacture)
        {
            if(_node.manufactureMap.count(scsManufacture.itemId))
            {
                // find new manufacture
                _node.manufactureMap.insert(std::make_pair(scsManufacture.itemId, scsManufacture));
            } else {
                // TODO manufacture已经被注册过了, throw error
            }

            // collect item id
            scs::entity::ScsItem it_1;
            this->make_sure_item(_node.itemMap, scsManufacture.itemId, it_1);

            for(ScsConfigComponent scsComp : scsManufacture.componentList)
            {
                // collect production raw material
                scs::entity::ScsItem it_2;
                this->make_sure_item(_node.itemMap, scsComp.itemId, it_2);
            }
        }
    }
}

/**
 * process edge
 * @param edge ScsConfigEdge list
 */
void ScsGraph::_processEdge(const std::vector<ScsConfigEdge> &edge)
{
    std::string leftNodeId = "";
    std::string rightNodeId = "";

    for(ScsConfigEdge scsEdge : edge)
    {
        // path
        std::string _p = scsEdge.path;

        // remove brackets
        std::string wrk_target = "(";
        _p.replace(_p.find(wrk_target), wrk_target.length(), "");

        wrk_target = ")";
        _p.replace(_p.find(wrk_target), wrk_target.length(), "");

        wrk_target = " ";
        _p.replace(_p.find(wrk_target), wrk_target.length(), "");

        wrk_target = ",";
        int splitPoint = _p.find(wrk_target);

        leftNodeId = _p.substr(0, splitPoint);
        rightNodeId = _p.substr(splitPoint + 1);

        // left node
        ScsNode _node;
        this->make_sure_node(leftNodeId, _node);
        for(std::string it : scsEdge.items)
        {
            ScsItem it_obj;
            this->make_sure_item(_node.itemMap, it, it_obj);
        }
        // right node
        ScsNode _node2;
        this->make_sure_node(rightNodeId, _node2);
        for(std::string it : scsEdge.items)
        {
            ScsItem it_obj;
            this->make_sure_item(_node.itemMap, it, it_obj);
        }
    }
}

/**
 * process cost
 * @param cost ScsConfigCost list
 * @param costType CostType
 */
void ScsGraph::_processCost(const std::vector<ScsConfigCost> &cost, const scs::enums::CostType &costType)
{
    for(ScsConfigCost scsCost : cost)
    {
        // fetch all nodes from cost declaration
        ScsNode _node;
        this->make_sure_node(scsCost.nodeId, _node);

        for(ScsConfigFunc scsFunc : scsCost.funcList)
        {
            // item
            ScsItem it_obj;
            this->make_sure_item(_node.itemMap, scsFunc.itemId, it_obj);

            // function
            if(it_obj.functionMap.count(costType))
            {
                it_obj.functionMap[costType].insert(scsFunc.funcId);
            } else {
                std::unordered_set<std::string> funcSet;
                funcSet.insert(scsFunc.funcId);
                it_obj.functionMap[costType] = funcSet;
            }
        }
    }
}

/**
 * make sure target nodeId exist in nodeMap
 * @param nodeId node id
 * @param node ScsNode object
 */
void ScsGraph::make_sure_node(const std::string &nodeId, ScsNode &node)
{
    if(this->nodeMap.count(nodeId))
    {
        node = this->nodeMap[nodeId];
    } else {
        // find new node
        this->nodeMap.insert(std::make_pair(nodeId, node));
    }
}



/**
 * make sure target itemId exist in itemMap
 * @param itemMap item map
 * @param itemId item id
 * @param item ScsItem object
 */
void ScsGraph::make_sure_item(std::map<std::string, ScsItem> &itemMap, const std::string &itemId, const ScsItem &item)
{
    if(itemMap.count(itemId))
    {
        // target item id already exist
        std::stringstream sout;
        sout << "Repeatedly defining an item: " << itemId;
        throw std::runtime_error(sout.str());
    } else {
        // find undeclared item
        itemMap.insert(std::make_pair(itemId, item));
    }
}

/**
 * varify graph structure
 */
void ScsGraph::verify()
{
    // TODO verify()
}

}}

#endif /* SCS_GRAPH_CPP */
