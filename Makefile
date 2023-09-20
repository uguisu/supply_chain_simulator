# Copyright (c) 2022
# All rights reserved.
#
# Author: xin he

BUILD_DIR := ./build
SRC_DIRS := ./src

# Flag for implicit rules. Turn on debug info
CXXFLAGS = -g -std=c++11

# Target: ALL
all : _lib _test done_message

.PHONY : all

# Find all the C and C++ files we want to compile
# Note the single quotes around the * expressions. Make will incorrectly expand these otherwise.
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c')

# build test
_test:
	@echo "🐞 Building test..."
	$(CXX) \
	$(CXXFLAGS) \
	$(SRCS) \
	-l glog \
	-l gflags \
	-pthread \
	-o ./build/scs_test

test: _lib _test done_message

.PHONY : test

# build lib
_lib:
	@echo "🌱 Building lib..."
	$(CXX) \
	$(CXXFLAGS) \
	$(SRCS) \
	-fPIC \
	-shared \
	-pthread \
	-o ./build/libscs.so

lib: _lib done_message
.PHONY : lib

.PHONY : clean
clean:
	$(RM) ./build/*

.PHONY : done_message
done_message:
	@echo "🌲 Done ===="
