// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef SCS_MAIN_HPP
#define SCS_MAIN_HPP

#include <string>
#include <Python.h>

namespace scs { namespace core {

/**
 * build graph
 * @param jsonFileWithPath config file with path
 */
void build_graph(const std::string &jsonFileWithPath);

/**
 * convert build graph
 * @param py_json_file_with_path config file with path
 */
static PyObject * Convert_build_graph(PyObject * self, PyObject * py_json_file_with_path);

/**
 * declare python method
 */
static PyMethodDef scs_methods[] = {
    // The first property is the name exposed to Python, fast_tanh
    // The second is the C++ function with the implementation
    // METH_O means it takes a single PyObject argument
    { "build_graph", (PyCFunction)Convert_build_graph, METH_O, nullptr },

    // Terminate the array with an object containing nulls.
    { nullptr, nullptr, 0, nullptr }
};

/**
 * declare python model
 */
static PyModuleDef scs_module = {
    PyModuleDef_HEAD_INIT,
    // Module name to use with Python import statements
    "scs",
    // Module description
    "supply chain simulator",
    0,
    // Structure that defines the methods of the module
    scs_methods
};

PyMODINIT_FUNC PyInit_scs();

}}

#endif /* SCS_MAIN_HPP */
