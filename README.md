# Supply_chain_simulator

![logo](assets/logo.jpg)

<p align="center">
    <img src="https://img.shields.io/badge/Apache-2.0-blue" alt="license" />
    <a href=https://996.icu/#/zh_CN>
        <img src="https://img.shields.io/badge/license-Anti%20996-blue.svg" alt="license" />
    </a>
    <img src="https://img.shields.io/badge/Python-3.8-red" alt="py38" />
</p>

## About
A Supply Chain Simulator

This project will emulate a supply chain graph, include( but not limitate ):
- Inventory
- Manufacturer
- Transport
- Retailer
- Consumer

All production and transportation processes will be abstracted into a function.
Users can re-write these functions(or declare new functions) to handle their real scene.

## Dependence
- [glog v0.6.0](https://github.com/google/glog)
- [gflag v2.2.2](https://github.com/gflags/gflags)
- [nlohmann/json v3.11.2](https://github.com/nlohmann/json)
- python 3.8 ( python3.8-dev / python3.8-venv / virtualenv )

## Requirements
Click [here](docs/requirements.md) to view all internal requirements.

## Build C++

To build all project, just execute:
```shell
make
```

Build goal list:
- `make clean` clean all build cache
- `make lib` build `.so` library
- `make test` build test program
- `make py` build python extension module

## Build Python lib manually

`make py` is an automatic script to build python extension module.

Users who do not familiar with `make` command can build above module manually.

```sh
# active python virtual env
# source <PATH>/venv/bin/activate

cd ./py_wrapper_src/scs
CC=g++ python setup.py install
```

:bulb: Tips:
- To avoid contaminating the system and Python setup, it is best to use a Python virtual environment
- In the python build path, create a soft link to the C++ build path. This will help keep the project tidy. Example: `cd ./py_wrapper_src/scs && ln -s ../../build/ ./build`

## Example
To to use this project, user should specify a [config file](docs/config_example.json) which include all node/edge/items.

```c++
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

    // show report ===============
    LOG(INFO) << graph.report()
}
```

After call `report()` method, graph object will output a shot report to let user confirm whether the graph config is correct.
```log
================== Graph Report ==================
Total nodes: 4
Total edges: 3
Total items: 3
--------------------------------------------------
Formula: n_3 :: C
  - 1 * A + 2 * B
======================================== END =====
```

## Reference
- [Definition](docs/definition.md)
