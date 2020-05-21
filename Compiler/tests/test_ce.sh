#!/bin/bash
cp ../AST AST
for file in $(cat CE)
do
  ./AST $file
done