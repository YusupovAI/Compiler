#!/bin/bash
cp ../AST AST
for file in $(ls CE)
do
  ./AST CE/$file
done