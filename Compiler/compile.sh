#!/bin/bash
mkdir build
cd build
cmake ..
make 
mv AST ..
cd ..
rm -rf build
