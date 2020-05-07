#!/bin/bash
cp ../AST AST
for file in $(cat)
do
  ./AST $file -print
done