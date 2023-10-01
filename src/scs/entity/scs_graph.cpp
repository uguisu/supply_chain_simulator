// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef SCS_GRAPH_CPP
#define SCS_GRAPH_CPP

#include <string>
#include <vector>
// #include <sstream>
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
    this->_processLoLs(config.lo, scs::enums::CostType::Order);

    // Field: ls
    this->_processLoLs(config.ls, scs::enums::CostType::Shipment);

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
 * process LO/LS
 * @param lols ScsConfigLoLs object
 * @param costType CostType
 */
void ScsGraph::_processLoLs(const std::vector<ScsConfigLoLs> &lols, const scs::enums::CostType &costType)
{
    std::string leftNodeId = "";
    std::string rightNodeId = "";

    for(ScsConfigLoLs scsLols : lols)
    {
        // path
        this->splitPath(scsLols.path, leftNodeId, rightNodeId);

        // left node
        ScsNode _lnode = this->make_sure_node(leftNodeId);
        // right node
        ScsNode _rnode = this->make_sure_node(rightNodeId);

        for(ScsConfigFunc scsFunc : scsLols.funcList)
        {
            ScsEdge _edge;
            _edge.fromNodeId = leftNodeId;
            _edge.toNodeId = rightNodeId;
            _edge.itemId = scsFunc.itemId;

            if(costType == scs::enums::CostType::Order)
            {
                _edge.loFuncId = scsFunc.funcId;
            }
            if(costType == scs::enums::CostType::Shipment)
            {
                _edge.lsFuncId = scsFunc.funcId;
            }
        }
    }
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
        ScsNode _node = this->make_sure_node(scsFormula.nodeId);

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
        this->splitPath(scsEdge.path, leftNodeId, rightNodeId);

        // left node
        ScsNode _node = this->make_sure_node(leftNodeId);
        for(std::string it : scsEdge.items)
        {
            ScsItem it_obj;
            this->make_sure_item(_node.itemMap, it, it_obj);
        }
        // right node
        ScsNode _node2 = this->make_sure_node(rightNodeId);
        for(std::string it : scsEdge.items)
        {
            ScsItem it_obj;
            this->make_sure_item(_node2.itemMap, it, it_obj);
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
        ScsNode _node = this->make_sure_node(scsCost.nodeId);

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
 * @return ScsNode object
 */
const ScsNode & ScsGraph::make_sure_node(const std::string &nodeId)
{
    ScsNode *rtn;

    if(this->nodeMap.count(nodeId))
    {
        rtn = &(this->nodeMap[nodeId]);
    } else {

        // find new node
        rtn = new ScsNode;
        (*rtn).id = nodeId;
        this->nodeMap.insert(std::make_pair(nodeId, (*rtn)));
    }

    return *rtn;
}

/**
 * make sure target itemId exist in itemMap
 * @param itemMap item map
 * @param itemId item id
 * @param item ScsItem object
 */
void ScsGraph::make_sure_item(std::map<std::string, ScsItem> &itemMap, const std::string &itemId, ScsItem &item)
{
    if(itemMap.count(itemId))
    {
        // target item id already exist
        item = itemMap[itemId];
    } else {
        // find undeclared item
        item.id = itemId;
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

/**
 * split path
 * @param path path, like "(1, 2)"
 * @param leftP left path
 * @param rightP right path
 */
void ScsGraph::splitPath(const std::string &path, std::string &leftP, std::string &rightP)
{
    // path
    std::string _p = path;

    // remove brackets
    std::string wrk_target = "(";
    _p.replace(_p.find(wrk_target), wrk_target.length(), "");

    wrk_target = ")";
    _p.replace(_p.find(wrk_target), wrk_target.length(), "");

    wrk_target = " ";
    _p.replace(_p.find(wrk_target), wrk_target.length(), "");

    wrk_target = ",";
    int splitPoint = _p.find(wrk_target);

    leftP = _p.substr(0, splitPoint);
    rightP = _p.substr(splitPoint + 1);
}

}}

#endif /* SCS_GRAPH_CPP */
