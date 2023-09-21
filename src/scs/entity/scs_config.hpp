// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef SCS_CONFIG_HPP
#define SCS_CONFIG_HPP

#include <string>
#include <vector>

namespace scs { namespace entity {

// pre-declare class
class ScsConfig;
// For: "lo", "ls"
class ScsConfigLoLs;
// For: "formula"
class ScsConfigFormula;
// For: "edges"
class ScsConfigEdge;
// For: "holding_cost", "shortage_cost", "consumer"
class ScsConfigCost;
// TODO 残值成本函数

// For: "func"
class ScsConfigFunc;
// For: "manufacture"
class ScsConfigManufacture;
// For: "component"
class ScsConfigComponent;


class ScsConfigFunc
{
    public:
        /** item id */
        std::string itemId;
        /** function id */
        std::string funcId;

        ~ScsConfigFunc() {};
};

class ScsConfigCost
{
    public:
        /** node id */
        std::string nodeId;
        /** function list */
        std::vector<ScsConfigFunc> funcList;

        ~ScsConfigCost() {};
};

class ScsConfigEdge
{
    public:
        /** path */
        std::string path;
        /** item list */
        std::vector<std::string> items;

        ~ScsConfigEdge() {};
};

class ScsConfigComponent
{
    public:
        /** item id */
        std::string itemId;
        /** materials */
        float materials;

        ~ScsConfigComponent() {};
};

class ScsConfigManufacture
{
    public:
        /** item id */
        std::string itemId;
        /** process time */
        float processTime;
        /** component list */
        std::vector<ScsConfigComponent> componentList;

        ~ScsConfigManufacture() {};
};

class ScsConfigFormula
{
    public:
        /** node id */
        std::string nodeId;
        /** manufacture */
        std::vector<ScsConfigManufacture> manufacture;

        ~ScsConfigFormula() {};
};

class ScsConfigLoLs
{
    public:
        /** path */
        std::string path;
        /** function list */
        std::vector<ScsConfigFunc> funcList;

        ~ScsConfigLoLs() {};
};

class ScsConfig
{
    public:

        /** lo */
        std::vector<ScsConfigLoLs> lo;
        /** ls */
        std::vector<ScsConfigLoLs> ls;
        /** formula */
        std::vector<ScsConfigFormula> formula;
        /** edges */
        std::vector<ScsConfigEdge> edges;
        /** holding cost */
        std::vector<ScsConfigCost> holdingCost;
        /** shortage cost */
        std::vector<ScsConfigCost> shortageCost;
        /** consumer */
        std::vector<ScsConfigCost> consumer;
        // TODO 残值成本函数

        /**
         * getNodeAmount
         */
        int16_t getNodeAmount();

        ~ScsConfig();
};

}}

#endif /* SCS_CONFIG_HPP */
