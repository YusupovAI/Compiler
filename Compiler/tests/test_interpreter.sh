#!/bin/bash
cp ../AST AST
for file in $(cat Interpreting)
do
  ./AST $file -interpret
done