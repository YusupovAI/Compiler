#!/bin/bash
cp ../AST AST
for file in $(ls Printing)
do
  ./AST Printing/$file -print
done