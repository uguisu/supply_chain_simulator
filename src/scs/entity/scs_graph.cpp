// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef SCS_GRAPH_CPP
#define SCS_GRAPH_CPP

#include <string>
#include <vector>
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
        this->make_sure_node(leftNodeId);
        // right node
        this->make_sure_node(rightNodeId);

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
        this->make_sure_node(scsFormula.nodeId);

        // fetch all manufacture
        for(int i = 0; i < scsFormula.manufacture.size(); i++)
        {
            // save manufacture info
            this->make_sure_manufacture(scsFormula.nodeId, scsFormula.manufacture[i]);


            // TODO
            // // collect item id
            // this->make_sure_item(scsFormula.nodeId, scsManufacture.itemId);

            // for(ScsConfigComponent scsComp : scsManufacture.componentList)
            // {
            //     // collect production raw material
            //     this->make_sure_item(scsFormula.nodeId, scsComp.itemId);
            // }
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
        this->make_sure_node(leftNodeId);
        for(std::string it : scsEdge.items)
        {
            this->make_sure_item(leftNodeId, it);
        }
        // right node
        this->make_sure_node(rightNodeId);
        for(std::string it : scsEdge.items)
        {
            this->make_sure_item(rightNodeId, it);
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
        this->make_sure_node(scsCost.nodeId);

        for(ScsConfigFunc scsFunc : scsCost.funcList)
        {
            // item
            ScsItem it_obj = this->make_sure_item(scsCost.nodeId, scsFunc.itemId);

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
 */
void ScsGraph::make_sure_node(const std::string &nodeId)
{
    if(this->nodeMap.count(nodeId))
    {
        // target node id already exist, skip
    } else {

        // find new node
        ScsNode *rtn = new ScsNode;
        (*rtn).id = nodeId;
        this->nodeMap.insert(std::make_pair(nodeId, (*rtn)));
    }
}

/**
 * make sure target itemId exist in itemMap
 * @param nodeId node id
 * @param itemId item id
 */
const ScsItem & ScsGraph::make_sure_item(const std::string &nodeId, const std::string &itemId)
{
    ScsItem *rtn;
    if(this->nodeMap[nodeId].itemMap.count(itemId))
    {
        // target item id already exist, skip
        rtn = &(this->nodeMap[nodeId].itemMap[itemId]);
    } else {
        // find undeclared item
        rtn = new ScsItem;
        (*rtn).id = itemId;
        this->nodeMap[nodeId].itemMap.insert(std::make_pair(itemId, (*rtn)));
    }

    return *rtn;
}

/**
 * make sure target manufacture exist in manufactureMap
 * @param nodeId node id
 * @param manuF ScsConfigManufacture object
 */
void ScsGraph::make_sure_manufacture(const std::string &nodeId, const ScsConfigManufacture &manuF)
{
    if(this->nodeMap[nodeId].manufactureMap.count(manuF.itemId))
    {
        // target item id already exist, skip
    } else {
        // find undeclared item
        // ScsConfigManufacture *pm = new ScsConfigManufacture(manuF);
        this->nodeMap[nodeId].manufactureMap.insert(std::make_pair(manuF.itemId, manuF));
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
