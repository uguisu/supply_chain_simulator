# Copyright (c) 2022
# All rights reserved.
#
# Author: xin he

BUILD_DIR := ./build
SRC_DIRS := ./src

# Flag for implicit rules. Turn on debug info
CXXFLAGS = -g -std=c++11

# Target: ALL
all : scs_test
	@echo "🌲 Done"

.PHONY : all

# Find all the C and C++ files we want to compile
# Note the single quotes around the * expressions. Make will incorrectly expand these otherwise.
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c')

# build scs_test
scs_test:
	@echo "🌱 Building..."
	$(CXX) \
    $(CXXFLAGS) \
    $(SRCS) \
    -l glog \
    -l gflags \
    -pthread \
    -o ./build/scs_test


.PHONY : clean
clean:
	$(RM) ./build/*
