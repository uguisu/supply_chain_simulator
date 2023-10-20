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
    // The first property is the name exposed to Python, build_graph
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
    // PyModuleDef_HEAD_INIT is a member of type PyModuleDef_Base,
    // which is advised to have just this one value.
    PyModuleDef_HEAD_INIT,
    // Module name to use with Python import statements
    "scs",
    // Module description. The string is the value that represents your module docstring.
    // You can use NULL to have no docstring, or you can specify a docstring by passing
    // a const char * as shown in the snippet above. It is of type Py_ssize_t.
    // You can also use PyDoc_STRVAR() to define a docstring for your module.
    "supply chain simulator",
    // -1 is the amount of memory needed to store your program state.
    // It’s helpful when your module is used in multiple subinterpreters, and it can have the following values:
    //   - A negative value indicates that this module doesn’t have support for subinterpreters.
    //   - A non-negative value enables the re-initialization of your module. It also specifies the memory
    //     requirement of your module to be allocated on each subinterpreter session.
    -1,
    // Structure that defines the methods of the module
    scs_methods
};

// When a Python program imports your module for the first time, it will call PyInit_scs()
PyMODINIT_FUNC PyInit_scs();

}}

#endif /* SCS_MAIN_HPP */
