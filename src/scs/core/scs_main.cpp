// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef SCS_MAIN_CPP
#define SCS_MAIN_CPP

#include <iostream>

#include "../entity/scs_config.hpp"
#include "../entity/scs_graph.hpp"
#include "scs_main.hpp"

namespace scs { namespace core {

/**
 * build graph
 * @param jsonFileWithPath config file with path
 */
void build_graph(const std::string &jsonFileWithPath)
{
    // read config info from json file
    scs::entity::ScsConfig config;
    config.read(jsonFileWithPath);

    // build graph
    scs::entity::ScsGraph graph;
    graph.build(config);

    // TODO next step ===============
}

/**
 * convert build graph
 * @param py_json_file_with_path config file with path
 */
static PyObject * Convert_build_graph(PyObject * self, PyObject * py_json_file_with_path)
{
    /* Parse arguments */
    std::string * py_json_f;
    if(!PyArg_ParseTuple(py_json_file_with_path, "S", &py_json_f)) {
        return NULL;
    }
    
    // call real function
    build_graph(*py_json_f);

    // return null
    return (PyObject *)(Py_BuildValue(""));
}

PyMODINIT_FUNC PyInit_scs() {
    return PyModule_Create(&scs_module);
};

}}

#endif /* SCS_MAIN_CPP */
