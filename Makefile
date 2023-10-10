# Copyright (c) 2022
# All rights reserved.
#
# Author: xin he

BUILD_DIR := ./build
SRC_DIRS := ./src/scs
SRC_TEST_DIRS := ./src

# specify your python version
PYTHON_VERSION := python3.8
PYTHON_HEADER_DIR := /usr/include/$(PYTHON_VERSION)

# Flag for implicit rules. Turn on debug info
CXXFLAGS = -g -std=c++11

# Target: ALL
all : _lib _test done_message

.PHONY : all

# Find all the C and C++ files we want to compile
# Note the single quotes around the * expressions. Make will incorrectly expand these otherwise.
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c')
SRCS_TEST := $(shell find $(SRC_TEST_DIRS) -name '*.cpp' -or -name '*.c')

# build lib
_lib:
	@echo "🌱 Building lib..."
	$(CXX) \
	$(CXXFLAGS) \
	$(SRCS) \
	-fPIC \
	-l $(PYTHON_VERSION) \
	-I $(PYTHON_HEADER_DIR) \
	-shared \
	-pthread \
	-o $(BUILD_DIR)/libscs.so

lib: _lib done_message
.PHONY : lib

# build test
_test:
	@echo "🐞 Building test..."
	$(CXX) \
	$(CXXFLAGS) \
	$(SRCS_TEST) \
	-l glog \
	-l gflags \
	-l $(PYTHON_VERSION) \
	-I $(PYTHON_HEADER_DIR) \
	-pthread \
	-o $(BUILD_DIR)/scs_test

test: _test done_message
.PHONY : test

# build python extension module
_py_extension_module:
	@echo "🐍 Building python extension module..."

py: _py_extension_module done_message
.PHONY : py

clean:
	@$(RM) $(BUILD_DIR)/*
.PHONY : clean

done_message:
	@echo "🎖️  Done ===="
.PHONY : done_message
