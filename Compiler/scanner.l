
%{
    #include <cerrno>
    #include <climits>
    #include <cstdlib>
    #include <cstring> 
    #include <string>
    #include <iostream>
    #include "driver.h"
    #include "parser.h"
%}

%option noyywrap nounput noinput batch debug

%option c++
%option yyclass="Scanner"

%{
  yy::parser::symbol_type make_NUMBER(
    const std::string &s,
    const yy::location& location
  );
%}

id [a-zA-Z][a-zA-Z0-9_]*
int [0-9]+
blank [ \t\r ]

%{
  # define YY_USER_ACTION  loc.columns (yyleng);
%}

%%

%{
  // A handy shortcut to the location held by the driver.
  yy::location& loc = driver_.GetLocation();
  // Code run each time yylex is called.
  loc.step();
%}

{blank}+ {
  loc.step();
}

\n+ {
  loc.lines(yyleng);
  loc.step();
}

"main" {
  return yy::parser::make_MAIN(loc);
}

"class" {
  return yy::parser::make_CLASS(loc);
}

"public" {
  return yy::parser::make_PUBLIC(loc);
}

"static" {
  return yy::parser::make_STATIC(loc);
}

"void" {
  return yy::parser::make_VOID(loc);
}

"int" {
  return yy::parser::make_INT(loc);
}

"boolean" {
  return yy::parser::make_BOOLEAN(loc);
}

"System\.out\.println" {
  return yy::parser::make_PRINT(loc);
}

"return" {
  return yy::parser::make_RETURN(loc);
}


"{" {
  return yy::parser::make_LBRACE(loc);
}

"}" {
  return yy::parser::make_RBRACE(loc);
}

"[]" {
  return yy::parser::make_BRACKETS(loc);
}

"[" {
  return yy::parser::make_LBRACKET(loc);
}

"]" {
  return yy::parser::make_RBRACKET(loc);
}

";" {
  return yy::parser::make_STATEMENT_END(loc);
}

"-" {
  return yy::parser::make_MINUS(loc);
}

"+" {
  return yy::parser::make_PLUS(loc);
}

"*" {
  return yy::parser::make_MUL(loc);
}

"/" {
  return yy::parser::make_DIV(loc);
}

"(" {
  return yy::parser::make_LPAREN (loc);
}

")" {
  return yy::parser::make_RPAREN (loc);
}

"==" {
  return yy::parser::make_EQUAL(loc);
}

"=" {
  return yy::parser::make_ASSIGN (loc);
}

"&&" {
  return yy::parser::make_AND(loc);
}

"||" {
  return yy::parser::make_OR(loc);
}

"<" {
  return yy::parser::make_LESS(loc);
}

">" {
  return yy::parser::make_GREATER(loc);
}

"%" {
  return yy::parser::make_MOD(loc);
}

"." {
  return yy::parser::make_DOT(loc);
}

"," {
  return yy::parser::make_COMMA(loc);
}

"extends" {
  return yy::parser::make_EXTENDS(loc);
}

"assert" {
  return yy::parser::make_ASSERT(loc);
}

"if" {
  return yy::parser::make_IF(loc);
}

"else" {
  return yy::parser::make_ELSE(loc);
}

"while" {
  return yy::parser::make_WHILE(loc);
}

"this" {
  return yy::parser::make_THIS(loc);
}

"true" {
  return yy::parser::make_TRUE(loc);
}

"false" {
  return yy::parser::make_FALSE(loc);
}

"new" {
  return yy::parser::make_NEW(loc);
}

"!" {
  return yy::parser::make_NOT(loc);
}

"length" {
  return yy::parser::make_LENGTH(loc);
}

{int} {
  return make_NUMBER(yytext, loc);
}

{id} {
  return yy::parser::make_IDENTIFIER(yytext, loc);
}

. {
  throw yy::parser::syntax_error(loc, "invalid character: " + std::string(yytext));
}

<<EOF>> {
  return yy::parser::make_END (loc);
}

%%

yy::parser::symbol_type make_NUMBER(
  const std::string &s,
  const yy::parser::location_type& loc
) {
  errno = 0;
  long n = strtol(s.c_str(), NULL, 10);
  if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
    throw yy::parser::syntax_error(loc, "integer is out of range: " + s);
  return yy::parser::make_NUMBER((int) n, loc);
}