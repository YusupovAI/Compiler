#pragma once

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL yy::parser::symbol_type Scanner::ScanToken()

#include "parser.h"

class Driver;

class Scanner: public yyFlexLexer {
 public:
  
  Scanner(Driver& driver): driver_(driver) {}

  virtual ~Scanner() {}
	
  virtual yy::parser::symbol_type ScanToken();

  Driver& GetDriver();

private:
    Driver &driver_;
};