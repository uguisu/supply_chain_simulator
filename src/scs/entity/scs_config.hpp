// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef SCS_CONFIG_HPP
#define SCS_CONFIG_HPP

#include <string>
#include <vector>

#include <nlohmann/json.hpp>

using json = nlohmann::json;


namespace scs { namespace entity {

// declare field name
const std::string FIELD_ITEM_ID = "item_id";
const std::string FIELD_FUNC_ID = "func_id";
const std::string FIELD_NODE_ID = "node_id";
const std::string FIELD_PATH = "path";
const std::string FIELD_FUNC_LIST = "func_list";
const std::string FIELD_LO = "lo";
const std::string FIELD_LS = "ls";
const std::string FIELD_HOLDING_COST = "holding_cost";
const std::string FIELD_SHORTAGE_COST = "shortage_cost";
const std::string FIELD_SALVAGE_COST = "salvage_cost";
const std::string FIELD_CONSUMER = "consumer";
const std::string FIELD_EDGES = "edges";
const std::string FIELD_ITEMS = "items";
const std::string FIELD_PROCESS_TIME = "process_time";
const std::string FIELD_COMPONENT_LIST = "component_list";
const std::string FIELD_MANUFACTURE = "manufacture";
const std::string FIELD_FORMULA = "formula";
const std::string FIELD_MATERIAL= "materials";

// pre-declare class
class ScsConfig;
// For: "lo", "ls"
class ScsConfigLoLs;
// For: "formula"
class ScsConfigFormula;
// For: "edges"
class ScsConfigEdge;
// For: "holding_cost", "shortage_cost", "salvage_cost", "consumer"
class ScsConfigCost;

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

        /**
         * setup value
         */
        void from_json(const json &jsonObject);

        ~ScsConfigFunc() {};
};

class ScsConfigCost
{
    public:
        /** node id */
        std::string nodeId;
        /** function list */
        std::vector<ScsConfigFunc> funcList;

        /**
         * setup value
         */
        void from_json(const json &jsonObject);

        ~ScsConfigCost() {};
};

class ScsConfigEdge
{
    public:
        /** path */
        std::string path;
        /** item list */
        std::vector<std::string> items;

        /**
         * setup value
         */
        void from_json(const json &jsonObject);

        ~ScsConfigEdge() {};
};

class ScsConfigComponent
{
    public:
        /** item id */
        std::string itemId;
        /** materials */
        float materials;

        /**
         * ScsConfigComponent - default construct
         */
        ScsConfigComponent() {};

        /**
         * ScsConfigComponent - clone construct
         */
        ScsConfigComponent(const ScsConfigComponent &original);

        /**
         * setup value
         */
        void from_json(const json &jsonObject);

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

        /**
         * setup value
         */
        void from_json(const json &jsonObject);

        /**
         * ScsConfigManufacture - default construct
         */
        ScsConfigManufacture() {};

        /**
         * ScsConfigManufacture - clone construct
         */
        ScsConfigManufacture(const ScsConfigManufacture &original);

        ~ScsConfigManufacture() {};
};

class ScsConfigFormula
{
    public:
        /** node id */
        std::string nodeId;
        /** manufacture */
        std::vector<ScsConfigManufacture> manufacture;

        /**
         * setup value
         */
        void from_json(const json &jsonObject);

        ~ScsConfigFormula() {};
};

class ScsConfigLoLs
{
    public:
        /** path */
        std::string path;
        /** function list */
        std::vector<ScsConfigFunc> funcList;

        /**
         * setup value
         */
        void from_json(const json &jsonObject);

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
        /** salvage cost */
        std::vector<ScsConfigCost> salvageCost;
        /** consumer */
        std::vector<ScsConfigCost> consumer;

        /**
         * read config values from json
         */
        void read(std::string jsonFileWithPath);

        ~ScsConfig() {};
    
    private:
        json jsonObject;

        /**
         * verify config info by rules
         */
        void verify();
};

}}

#endif /* SCS_CONFIG_HPP */


// refer https://zhuanlan.zhihu.com/p/387380942