%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert


%code requires {

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include "include_list.h"

using namespace AST;
class Driver;
class Scanner;

}

%define parse.trace
%define parse.error verbose

%code {
    #include "driver.h"
    #include "scanner.h"
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

%define api.token.prefix {TOK_}

%token
    END 0 "eof"
    ASSIGN "="
    MINUS "-"
    PLUS "+"
    LPAREN "("
    RPAREN ")"
    LBRACKET "["
    RBRACKET "]"
    BRACKETS "[]"
    AND "&&"
    OR "||"
    LESS "<"
    GREATER ">"
    EQUAL "=="
    MUL "*"
    DIV "/"
    MOD "%%"
    STATEMENT_END ";"
    PRINT "System.out.println"
    LBRACE "{"
    RBRACE "}"
    DOT "."
    COMMA ","
    EXTENDS "extends"
    INT "int"
    BOOLEAN "boolean"
    VOID "void"
    RETURN "return"
    ASSERT "assert"
    IF "if"
    WHILE "while"
    ELSE "else"
    THIS "this"
    TRUE "true"
    FALSE "false"
    NEW "new"
    NOT "!"
    LENGTH "length"
    CLASS "class"
    PUBLIC "public"
    STATIC "static"
    MAIN "main"
;

%token <std::string> IDENTIFIER "identifier";
%token <int> NUMBER "number";
%nterm <std::unique_ptr<Expression> > expression;
%nterm <std::unique_ptr<ClassDeclaration> > class_declaration;
%nterm <std::unique_ptr<ClassDeclarationList> > class_declaration_list;
%nterm <std::unique_ptr<Declaration> > declaration;
%nterm <std::unique_ptr<Formals> > formals;
%nterm <std::unique_ptr<MainClass> > main_class;
%nterm <std::unique_ptr<MethodDeclaration> > method_declaration;
%nterm <std::unique_ptr<Type> > ttype;
%nterm <std::unique_ptr<SimpleType> > simple_type;
%nterm <std::unique_ptr<ArrayType> > array_type;
%nterm <std::unique_ptr<Statement> > statement;
%nterm <std::unique_ptr<Formals> > formal_list;
%nterm <std::unique_ptr<MethodInvocation> > method_invocation;
%nterm <std::unique_ptr<LValue> > lvalue;
%nterm <std::unique_ptr<StatementList> > statements;
%nterm <std::unique_ptr<VariableDeclaration> > variable_declaration;
%nterm <std::unique_ptr<DeclarationList> > declaration_list;
%nterm <std::unique_ptr<FunctionArguments> > function_arguments;
%nterm <std::unique_ptr<FunctionArguments> > arguments_list;  
%nterm <std::unique_ptr<SimpleLValue> > lvalue_simple;
%nterm <std::unique_ptr<ArrayElementLValue> > lvalue_array_element;

%%
%start program;

program:
  main_class class_declaration_list {
    driver.SetProgram(std::make_unique<Program>(std::move($1), std::move($2)));
  };

class_declaration_list:
  %empty {
    $$ = std::make_unique<ClassDeclarationList>();
  } |
  class_declaration class_declaration_list {
    $$ = std::make_unique<ClassDeclarationList>(std::move($1), std::move($2));
  };

class_declaration:
  "class" "identifier" "{" declaration_list "}" {
    $$ = std::make_unique<ClassDeclarationSimple>(std::move($2), std::move($4));
  } |
  "class" "identifier" "extends" "identifier" "{" declaration_list "}" {
    $$ = std::make_unique<ClassDeclarationInheritted>(std::move($2), std::move($4), std::move($6));
  };

declaration_list:
  %empty {
    $$ = std::make_unique<DeclarationList>();
  } |
  declaration declaration_list {
    $$ = std::make_unique<DeclarationList>(std::move($1), std::move($2));
  };

declaration:
  variable_declaration {
    $$ = std::make_unique<DeclarationVariable>(std::move($1));
  } |
  method_declaration {
    $$ = std::make_unique<DeclarationMethod>(std::move($1));
  };

variable_declaration:
  ttype "identifier" ";" {
    $$ = std::make_unique<VariableDeclaration>(std::move($1), std::move($2));
  };

method_declaration:
  "public" ttype "identifier" "(" formals ")" "{" statements "}" {
    $$ = std::make_unique<MethodDeclaration>(std::move($2), std::move($3), std::move($5), std::move($8));
  };

ttype:
  simple_type {
    $$ = std::make_unique<TypeSimple>(std::move($1));
  } |
  array_type {
    $$ = std::make_unique<TypeArray>(std::move($1));
  };

simple_type:
  "int" {
    $$ = std::make_unique<SimpleType>(SimpleType::Int);
  } |
  "boolean" {
    $$ = std::make_unique<SimpleType>(SimpleType::Boolean);
  } |
  "void" {
    $$ = std::make_unique<SimpleType>(SimpleType::Void);
  } |
  "identifier" {
    $$ = std::make_unique<SimpleType>(std::move($1));
  };

array_type:
  simple_type "[]" {
    $$ = std::make_unique<ArrayType>(std::move($1));
  };

formals:
  %empty {
    $$ = std::make_unique<Formals>();
  } |
  ttype "identifier" formal_list {
    $$ = std::make_unique<Formals>(std::move($1), std::move($2), std::move($3));
  };

formal_list:
  %empty {
    $$ = std::make_unique<Formals>();
  } |
  "," ttype "identifier" formal_list {
    $$ = std::make_unique<Formals>(std::move($2), std::move($3), std::move($4));
  };

statements:
  %empty {
    $$ = std::make_unique<StatementList>();
  } |
  statement statements {
    $$ = std::make_unique<StatementList>(std::move($1), std::move($2));
  };

main_class:
  "class" "identifier" "{" "public" "static" "void" "main" "(" ")" "{" statements "}" "}" {
    $$ = std::make_unique<MainClass>(std::move($2), std::move($11));
  };

%left "then";
%left "else";
%left "&&" "||";
%right "!";
%left "<" "==" ">";
%left "+" "-";
%left "*" "/" "%%";
%left ".";
%left "[" "]";

statement:
  "assert" "(" expression ")" {
    $$ = std::make_unique<StatementAssert>(std::move($3));
  } |
  variable_declaration {
    $$ = std::make_unique<StatementVariableDeclaration>(std::move($1));
  } |
  "{" statements "}" {
    $$ = std::make_unique<StatementNewScope>(std::move($2));
  } |
  "if" "(" expression ")" statement %prec "then" {
    $$ = std::make_unique<StatementIfReduced>(std::move($3), std::move($5));
  } |
  "if" "(" expression ")" statement "else" statement {
    $$ = std::make_unique<StatementIfFull>(std::move($3), std::move($5), std::move($7));
  } |
  "while" "(" expression ")" statement {
    $$ = std::make_unique<StatementWhile>(std::move($3), std::move($5));
  } |
  "System.out.println" "(" expression ")" ";" {
    $$ = std::make_unique<StatementPrint>(std::move($3));
  } |
  lvalue "=" expression ";" {
    $$ = std::make_unique<StatementAssignment>(std::move($1), std::move($3));
  } |
  "return" expression ";" {
    $$ = std::make_unique<StatementReturn>(std::move($2));
  } |
  method_invocation ";" {
    $$ = std::make_unique<StatementMethodInvocation>(std::move($1));
  };

lvalue:
  lvalue_simple {
    $$ = std::make_unique<LValueSimple>(std::move($1));
  } |
  lvalue_array_element {
    $$ = std::make_unique<LValueArrayElement>(std::move($1));
  };

lvalue_array_element:
  expression "[" expression "]" {
    $$ = std::make_unique<ArrayElementLValue>(std::move($1), std::move($3));
  };

lvalue_simple:
  "identifier" {
    $$ = std::make_unique<SimpleLValue>(std::move($1));
  };

method_invocation:
  expression "." "identifier" "(" function_arguments ")" {
    $$ = std::make_unique<MethodInvocation>(std::move($1), std::move($3), std::move($5));
  };

function_arguments:
  %empty {
    $$ = std::make_unique<FunctionArguments>();
  } |
  expression arguments_list {
    $$ = std::make_unique<FunctionArguments>(std::move($1), std::move($2));
  };

arguments_list:
  %empty {
    $$ = std::make_unique<FunctionArguments>();
  } |
  "," expression arguments_list {
    $$ = std::make_unique<FunctionArguments>(std::move($2), std::move($3));
  };

expression:
  expression "["  expression "]" {
    $$ = std::make_unique<ExpressionArrayElement>(std::move($1), std::move($3));
  } |
  expression "." "length" {
    $$ = std::make_unique<ExpressionLength>(std::move($1));
  } |
  "new" simple_type "[" expression "]" {
    $$ = std::make_unique<ExpressionNewArray>(std::move($2), std::move($4));
  } |
  "new" "identifier" "(" ")" {
    $$ = std::make_unique<ExpressionNewVariable>(std::move($2));
  } |
  "!" expression {
    $$ = std::make_unique<ExpressionNot>(std::move($2));
  } |
  "(" expression ")" {
    $$ = std::make_unique<ExpressionBraces>(std::move($2));
  } |
  "identifier" {
    $$ = std::make_unique<ExpressionVariable>(std::move($1));
  } |
  "this" {
    $$ = std::make_unique<ExpressionThis>();
  } |
  "true"  {
    $$ = std::make_unique<ExpressionTrue>();
  } |
  "false" {
    $$ = std::make_unique<ExpressionFalse>();
  } |
  method_invocation {
    $$ = std::make_unique<ExpressionMethodInvocation>(std::move($1));
  } |
  "number" {
    $$ = std::make_unique<ExpressionNumber>($1);
  } |
  expression "+" expression {
    $$ = std::make_unique<ExpressionAdd>(std::move($1), std::move($3));
  } |
  expression "-" expression {
    $$ = std::make_unique<ExpressionSub>(std::move($1), std::move($3));
  } |
  expression "*" expression {
    $$ = std::make_unique<ExpressionMul>(std::move($1), std::move($3));
  } |
  expression "/" expression {
    $$ = std::make_unique<ExpressionDiv>(std::move($1), std::move($3));
  } |
  expression "&&" expression {
    $$ = std::make_unique<ExpressionAnd>(std::move($1), std::move($3));
  } |
  expression "||" expression {
    $$ = std::make_unique<ExpressionOr>(std::move($1), std::move($3));
  } |
  expression "==" expression {
    $$ = std::make_unique<ExpressionEqual>(std::move($1), std::move($3));
  } |
  expression "%%" expression {
    $$ = std::make_unique<ExpressionMod>(std::move($1), std::move($3));
  } |
  expression "<" expression {
    $$ = std::make_unique<ExpressionLess>(std::move($1), std::move($3));
  } |
  expression ">" expression {
    $$ = std::make_unique<ExpressionGreater>(std::move($1), std::move($3));
  };
  
%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
