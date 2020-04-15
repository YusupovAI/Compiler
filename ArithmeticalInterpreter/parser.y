%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {

#include <iostream>
#include <string>
#include <stdexcept>
class Scanner;
class Driver;
class Value;

}

%define parse.trace
%define parse.error verbose

%code {

#include "driver.h"
#include "location.hh"

static yy::parser::symbol_type yylex(Scanner &scanner, Driver& driver) {
  return scanner.ScanToken();
}

}

%lex-param { Scanner &scanner }
%lex-param { Driver &driver }
%parse-param { Scanner &scanner }
%parse-param { Driver &driver }

%locations

%define api.token.prefix {TOKEN_}

%token
  END 0 "EOF"
  CLASS "class"
  MINUS "-"
  PLUS "+"
  DIV "/"
  MUL "*"
  LPAREN "("
  RPAREN ")"
  ASSIGN "="
  PUBLIC "public"
  STATIC "static"
  VOID "void"
  MAIN "main"
  PRINT "System.out.println"
  LINE_END ";"
  LBRACKET "{"
  RBRACKET "}"
  INT "int"
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"
%nterm <int> expression;

%%
%start main_class;
main_class:
  "class" "identifier" "{" 
    "public" "static" "void" "main" "(" ")" "{"
      statement_list
    "}"
  "}";

statement_list:
    %empty |
    statement statement_list;

statement:
  "System.out.println" "(" expression ")" ";" {
    std::cout << $3 << '\n';
  } |
  "int" "identifier" ";" {
    if (driver.ContainsVariable($2)) {
      throw std::logic_error("Redeclaration of variable");  
    }
    driver.SetVariableValue($2, 0);
  } |
  "int" "identifier" "=" expression ";" {
    if (driver.ContainsVariable($2)) {
      throw std::logic_error("Redeclaration of variable");
    }
    driver.SetVariableValue($2, $4);
  } |
  "identifier" "=" expression ";" {
    if (!driver.ContainsVariable($1)) {
      throw std::logic_error("Usage of undeclared variable");  
    }
    driver.SetVariableValue($1, $3);
  };

%left "+" "-";
%left "*" "/";

expression:
    "number" | 
    "identifier" {
      $$ = driver.GetVariableValue($1);
    } | 
    expression "+" expression {
      $$ = $1 + $3; 
    } | 
    expression "-" expression {
      $$ = $1 - $3; 
    } | 
    expression "*" expression {
      $$ = $1 * $3; 
    } | 
    expression "/" expression {
      $$ = $1 / $3; 
    } | 
    "(" expression ")" {
      $$ = $2; 
    };

%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
