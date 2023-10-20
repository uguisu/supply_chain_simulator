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
#include <sstream>

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

    // verify
    this->verify();
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
        ScsNode * p_leftNode = this->make_sure_node(leftNodeId);
        // right node
        ScsNode * p_rightNode = this->make_sure_node(rightNodeId);

        for(ScsConfigFunc scsFunc : scsLols.funcList)
        {
            // genearte edge id
            std::string edgeId = this->generate_edge_id(leftNodeId, rightNodeId, scsFunc.itemId);
            ScsEdge * p_edge = this->make_sure_edge(edgeId);

            // edit edge object
            (*p_edge).fromNodeId = leftNodeId;
            (*p_edge).toNodeId = rightNodeId;
            (*p_edge).itemId = scsFunc.itemId;

            if(costType == scs::enums::CostType::Order)
            {
                (*p_edge).loFuncId = scsFunc.funcId;
            }
            if(costType == scs::enums::CostType::Shipment)
            {
                (*p_edge).lsFuncId = scsFunc.funcId;
            }

            // edit node's edge map
            this->make_sure_node_edge(
                p_leftNode, p_edge, scs::enums::NodeEdgeType::Left);
            this->make_sure_node_edge(
                p_rightNode, p_edge, scs::enums::NodeEdgeType::Right);
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
        ScsNode *p_node = this->make_sure_node(scsFormula.nodeId);

        // fetch all manufacture
        for(ScsConfigManufacture scsFormula : scsFormula.manufacture)
        {
            // save manufacture info
            ScsConfigManufacture *scsManufacture = this->make_sure_manufacture(p_node, scsFormula);

            // collect item id
            this->make_sure_item(p_node, (*scsManufacture).itemId);

            for(ScsConfigComponent scsComp : (*scsManufacture).componentList)
            {
                // collect production raw material
                this->make_sure_item(p_node, scsComp.itemId);
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
    std::string edgeId = "";

    for(ScsConfigEdge scsEdge : edge)
    {
        // path
        this->splitPath(scsEdge.path, leftNodeId, rightNodeId);

        // left node
        ScsNode *p_leftNode = this->make_sure_node(leftNodeId);
        // right node
        ScsNode *p_rightNode = this->make_sure_node(rightNodeId);

        for(std::string it : scsEdge.items)
        {
            // make sure item
            this->make_sure_item(p_leftNode, it);
            this->make_sure_item(p_rightNode, it);

            // genearte edge id
            edgeId = this->generate_edge_id(leftNodeId, rightNodeId, it);

            ScsEdge * p_edge = this->make_sure_edge(edgeId);
            // edit edge obbject
            (*p_edge).fromNodeId = leftNodeId;
            (*p_edge).toNodeId = rightNodeId;
            (*p_edge).itemId = it;
            // no need to edit lo/ls here

            // edit node's edge map
            this->make_sure_node_edge(
                p_leftNode, p_edge, scs::enums::NodeEdgeType::Left);
            this->make_sure_node_edge(
                p_rightNode, p_edge, scs::enums::NodeEdgeType::Right);
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
        ScsNode *p_node = this->make_sure_node(scsCost.nodeId);

        for(ScsConfigFunc scsFunc : scsCost.funcList)
        {
            // item
            ScsItem * it_obj = this->make_sure_item(p_node, scsFunc.itemId);

            // function
            if((*it_obj).functionMap.count(costType))
            {
                (*it_obj).functionMap[costType].insert(scsFunc.funcId);
            } else {
                std::unordered_set<std::string> funcSet;
                funcSet.insert(scsFunc.funcId);
                (*it_obj).functionMap[costType] = funcSet;
            }
        }
    }
}

/**
 * make sure target nodeId exist in nodeMap
 * @param nodeId node id
 * @return point of ScsNode object
 */
ScsNode * ScsGraph::make_sure_node(const std::string &nodeId)
{
    ScsNode *rtn;
    if(this->nodeMap.count(nodeId))
    {
        // target node id already exist
        rtn = this->nodeMap[nodeId];
    } else {
        // find new node
        rtn = new ScsNode();
        (*rtn).id = nodeId;
        this->nodeMap.insert(std::make_pair(nodeId, rtn));
    }

    return rtn;
}

/**
 * make sure target itemId exist in itemMap
 * @param p_node point of ScsNode object
 * @param itemId item id
 * @return point of ScsItem object
 */
ScsItem * ScsGraph::make_sure_item(ScsNode *p_node, const std::string &itemId)
{
    ScsItem *rtn;
    if((*p_node).itemMap.count(itemId))
    {
        // target item id already exist
        rtn = (*p_node).itemMap[itemId];
    } else {
        // find undeclared item
        rtn = new ScsItem;
        (*rtn).id = itemId;
        (*p_node).itemMap.insert(std::make_pair(itemId, rtn));
    }

    return rtn;
}

/**
 * make sure target manufacture exist in manufactureMap
 * @param p_node point of ScsNode object
 * @param manuF ScsConfigManufacture object
 * @return point of ScsConfigManufacture object
 */
ScsConfigManufacture * ScsGraph::make_sure_manufacture(ScsNode *p_node, const ScsConfigManufacture &manuF)
{
    ScsConfigManufacture *rtn;
    if((*p_node).manufactureMap.count(manuF.itemId))
    {
        // target item id already exist
        rtn = (*p_node).manufactureMap[manuF.itemId];
    } else {
        // find undeclared item
        rtn = new ScsConfigManufacture(manuF);
        (*p_node).manufactureMap.insert(std::make_pair(manuF.itemId, rtn));
    }

    return rtn;
}

/**
 * make sure target edgeId exist in edgeMap
 * @param edgeId edge id
 * @return point of ScsEdge object
 */
ScsEdge * ScsGraph::make_sure_edge(const std::string &edgeId)
{
    ScsEdge *rtn;
    if(this->edgeMap.count(edgeId))
    {
        // target edge id already exist
        rtn = this->edgeMap[edgeId];
    } else {
        // find new edge
        rtn = new ScsEdge();
        (*rtn).id = edgeId;
        this->edgeMap.insert(std::make_pair(edgeId, rtn));
    }

    return rtn;
}

/**
 * varify graph structure
 */
void ScsGraph::verify()
{
    // TODO verify()
}

/**
 * generate report
 * @return report as string
 */
std::string ScsGraph::report()
{
    // declare work node object
    ScsNode * p_node;
    // manufacture editor
    std::stringstream ssManufacture;
    ScsConfigComponent wrk_formula;
    int16_t wrk_formula_amount = 0;

    // calculate items
    std::unordered_set<std::string> itemSet;
    for(const std::pair<std::string, scs::entity::ScsNode*> wrk_pair : this->nodeMap)
    {
        // get node object
        p_node = wrk_pair.second;

        // go through Node
        for(const std::pair<std::string, scs::entity::ScsItem*> wrk_pair_item : (*p_node).itemMap)
        {
            itemSet.insert(wrk_pair_item.first);
        }

        // go through manufacture
        for(const std::pair<std::string, scs::entity::ScsConfigManufacture*> wrk_pair_manufacture : (*p_node).manufactureMap)
        {
            ssManufacture << "Formula: " << (*p_node).id << " :: " << wrk_pair_manufacture.first << "\n";
            wrk_formula_amount = wrk_pair_manufacture.second->componentList.size();
            for(int16_t idx = wrk_formula_amount; 0 < idx; idx--)
            {
                if(idx == wrk_formula_amount)
                {
                    ssManufacture << "  - ";
                }
                wrk_formula = wrk_pair_manufacture.second->componentList[wrk_formula_amount - idx];
                ssManufacture << wrk_formula.materials << " * " << wrk_formula.itemId;
                if(1 == idx)
                {
                    ssManufacture << "\n";
                } else {
                    ssManufacture << " + ";
                }
            }
        }
    }

    // declare stream
    std::stringstream ss;

    ss << "\n================== Graph Report ==================\n";
    ss << "Total nodes: " << this->nodeMap.size() << "\n";
    ss << "Total edges: " << this->edgeMap.size() << "\n";
    ss << "Total items: " << itemSet.size() << "\n";
    ss << "--------------------------------------------------\n";
    ss << ssManufacture.str();
    ss << "======================================== END =====\n";

    return ss.str();
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

ScsGraph::~ScsGraph()
{
    // delete point map "nodeMap"
    for(auto wrk_pair : this->nodeMap)
    {
        delete wrk_pair.second;
    }
    
    // delete point map "edgeMap"
    for(auto wrk_pair : this->edgeMap)
    {
        delete wrk_pair.second;
    }
}

/**
 * generate edge id
 * @param leftNodeId left node id
 * @param rightNodeId right node id
 * @param itemId item id
 * @return edge id
 */
std::string ScsGraph::generate_edge_id(
    const std::string &leftNodeId,
    const std::string &rightNodeId,
    const std::string &itemId)
{
    return leftNodeId + "_" + rightNodeId + "_" + itemId;
}

/**
 * make sure target edge saved in node
 * @param p_node point of ScsNode object
 * @param p_edge point of ScsEdge object
 * @param nodeEdgeType NodeEdgeType object
 */
void ScsGraph::make_sure_node_edge(
    ScsNode *p_node,
    ScsEdge *p_edge,
    const scs::enums::NodeEdgeType &nodeEdgeType)
{
    std::string edgeId = (*p_edge).id;

    if(scs::enums::NodeEdgeType::Right == nodeEdgeType)
    {
        if(0 == (*p_node).inputEdgeMap.count(edgeId))
        {
            (*p_node).inputEdgeMap.insert(std::make_pair(edgeId, p_edge));
        }
    }
    if(scs::enums::NodeEdgeType::Left == nodeEdgeType)
    {
        if(0 == (*p_node).outputEdgeMap.count(edgeId))
        {
            (*p_node).outputEdgeMap.insert(std::make_pair(edgeId, p_edge));
        }
    }
}

}}

#endif /* SCS_GRAPH_CPP */
