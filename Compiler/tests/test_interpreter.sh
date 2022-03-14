#!/bin/bash
cp ../AST AST
for file in $(ls Interpreting)
do
  ./AST Interpreting/$file -interpret
done