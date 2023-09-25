// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef SCS_CONFIG_CPP
#define SCS_CONFIG_CPP

#include <string>
#include <fstream>
#include <glog/logging.h>

#include "scs_config.hpp"

namespace scs { namespace entity {

    /**
     * read config values from json
     */
    void ScsConfig::read(std::string jsonFileWithPath)
    {
        // log
        LOG(INFO) << "Reading config file: " << jsonFileWithPath;

        std::ifstream f(jsonFileWithPath);
        // convert to json object
        this->jsonObject = json::parse(f);

        // field: lo
        for(auto &lo_item : jsonObject[FIELD_LO])
        {
            ScsConfigLoLs scll;
            scll.from_json(lo_item);
            this->lo.push_back(scll);
        }
        // field: ls
        for(auto &lo_item : jsonObject[FIELD_LS])
        {
            ScsConfigLoLs scll;
            scll.from_json(lo_item);
            this->ls.push_back(scll);
        }
        // field: edges
        for(auto &f_item : jsonObject[FIELD_FORMULA])
        {
            ScsConfigFormula scf;
            scf.from_json(f_item);
            this->formula.push_back(scf);
        }
        // field: edges
        for(auto &e_item : jsonObject[FIELD_EDGES])
        {
            ScsConfigEdge sce;
            sce.from_json(e_item);
            this->edges.push_back(sce);
        }
        // field: holding_cost
        for(auto &hc_item : jsonObject[FIELD_HOLDING_COST])
        {
            ScsConfigCost scc;
            scc.from_json(hc_item);
            this->holdingCost.push_back(scc);
        }
        // field: shortage_cost
        for(auto &sc_item : jsonObject[FIELD_SHORTAGE_COST])
        {
            ScsConfigCost scc;
            scc.from_json(sc_item);
            this->shortageCost.push_back(scc);
        }
        // field: salvage_cost
        for(auto &sc_item : jsonObject[FIELD_SALVAGE_COST])
        {
            ScsConfigCost scc;
            scc.from_json(sc_item);
            this->salvageCost.push_back(scc);
        }
        // field: consumer
        for(auto &c_item : jsonObject[FIELD_CONSUMER])
        {
            ScsConfigCost scc;
            scc.from_json(c_item);
            this->consumer.push_back(scc);
        }

        // verify all settings
        this->verify();
    }

    /**
     * verify config info by rules
     */
    void ScsConfig::verify()
    {
        // TODO throw error if there is an illegal value

    }

    /**
     * setup value
     */
    void ScsConfigFunc::from_json(const json &jsonObject)
    {
        jsonObject.at(FIELD_ITEM_ID).get_to(this->itemId);
        jsonObject.at(FIELD_FUNC_ID).get_to(this->funcId);
    }

    /**
     * setup value
     */
    void ScsConfigLoLs::from_json(const json &jsonObject)
    {
        jsonObject.at(FIELD_PATH).get_to(this->path);

        for(auto &func_item : jsonObject[FIELD_FUNC_LIST])
        {
            ScsConfigFunc scf;
            scf.from_json(func_item);
            this->funcList.push_back(scf);
        }
    }

    /**
     * setup value
     */
    void ScsConfigCost::from_json(const json &jsonObject)
    {
        jsonObject.at(FIELD_NODE_ID).get_to(this->nodeId);

        for(auto &func_item : jsonObject[FIELD_FUNC_LIST])
        {
            ScsConfigFunc scf;
            scf.from_json(func_item);
            this->funcList.push_back(scf);
        }
    }

    /**
     * setup value
     */
    void ScsConfigEdge::from_json(const json &jsonObject)
    {
        jsonObject.at(FIELD_PATH).get_to(this->path);

        for(auto &it_item : jsonObject[FIELD_ITEMS])
        {
            this->items.push_back(it_item);
        }
    }

    /**
     * setup value
     */
    void ScsConfigComponent::from_json(const json &jsonObject)
    {
        jsonObject.at(FIELD_ITEM_ID).get_to(this->itemId);
        jsonObject.at(FIELD_ITEM_ID).get_to(this->materials);
    }

    /**
     * setup value
     */
    void ScsConfigManufacture::from_json(const json &jsonObject)
    {
        jsonObject.at(FIELD_ITEM_ID).get_to(this->itemId);
        jsonObject.at(FIELD_PROCESS_TIME).get_to(this->processTime);

        for(auto &cl_item : jsonObject[FIELD_COMPONENT_LIST])
        {
            ScsConfigComponent scc;
            scc.from_json(cl_item);
            this->componentList.push_back(scc);
        }
    }

    /**
     * setup value
     */
    void ScsConfigFormula::from_json(const json &jsonObject)
    {
        jsonObject.at(FIELD_NODE_ID).get_to(this->nodeId);

        for(auto &m_item : jsonObject[FIELD_MANUFACTURE])
        {
            ScsConfigManufacture scm;
            scm.from_json(m_item);
            this->manufacture.push_back(scm);
        }
    }

}}

#endif /* SCS_CONFIG_CPP */