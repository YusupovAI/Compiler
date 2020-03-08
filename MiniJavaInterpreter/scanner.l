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
  // A number symbol corresponding to the value in S.
  yy::parser::symbol_type make_NUMBER(
    const std::string &s,
    const yy::location& location
  );
%}

id    [a-zA-Z][a-zA-Z_0-9]*
int   [0-9]+
blank [ \t\r]

%{
  // Code run each time a pattern is matched.
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

"System\.out\.println" {
  return yy::parser::make_PRINT(loc);
}

"{" {
  return yy::parser::make_LBRACKET(loc);
}

"}" {
  return yy::parser::make_RBRACKET(loc);
}

";" {
  return yy::parser::make_LINE_END(loc);
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

"=" {
  return yy::parser::make_ASSIGN (loc);
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