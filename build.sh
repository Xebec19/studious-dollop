#!/bin/bash

# Builds the project
mkdir -p build
cd build
cmake ..
make
