cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME AST)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(
  Parser
  parser.y
  ${CMAKE_SOURCE_DIR}/parser.cpp
  DEFINES_FILE ${CMAKE_SOURCE_DIR}/parser.h
  VERBOSE ${CMAKE_SOURCE_DIR}/conflicts.txt
)

FLEX_TARGET(
  Scanner
  scanner.l
  ${CMAKE_SOURCE_DIR}/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

add_executable(
  ${PROJECT_NAME}
  main.cpp
  ${BISON_Parser_OUTPUTS}
  ${FLEX_Scanner_OUTPUTS}
)

target_include_directories(
  ${PROJECT_NAME} 
  PUBLIC 
  ${CMAKE_SOURCE_DIR}
  Arguments
  ClassDeclaration
  CodeGenerator
  Core
  Declaration
  Expression
  LValue
  Method
  Statement
  Type
  Visitor
  Scopes
  Functions
  Classes
)

target_sources(
  ${PROJECT_NAME}
  PUBLIC
  driver.cpp
  main.cpp
  parser.cpp
  scanner.cpp
  Arguments/Formals.cpp
  Arguments/FunctionArguments.cpp
  ClassDeclaration/ClassDeclarationInheritted.cpp
  ClassDeclaration/ClassDeclarationList.cpp
  ClassDeclaration/ClassDeclarationSimple.cpp
  Core/MainClass.cpp
  Core/Program.cpp
  Declaration/DeclarationList.cpp
  Declaration/DeclarationMethod.cpp
  Declaration/DeclarationVariable.cpp
  Declaration/MethodDeclaration.cpp
  Declaration/VariableDeclaration.cpp
  Expression/ExpressionAdd.cpp
  Expression/ExpressionAnd.cpp
  Expression/ExpressionArrayElement.cpp
  Expression/ExpressionBraces.cpp
  Expression/ExpressionDiv.cpp
  Expression/ExpressionEqual.cpp
  Expression/ExpressionFalse.cpp
  Expression/ExpressionGreater.cpp
  Expression/ExpressionLength.cpp
  Expression/ExpressionLess.cpp
  Expression/ExpressionMethodInvocation.cpp
  Expression/ExpressionMod.cpp
  Expression/ExpressionMul.cpp
  Expression/ExpressionNewArray.cpp
  Expression/ExpressionNewVariable.cpp
  Expression/ExpressionNot.cpp
  Expression/ExpressionOr.cpp
  Expression/ExpressionSub.cpp
  Expression/ExpressionThis.cpp
  Expression/ExpressionTrue.cpp
  Expression/ExpressionVariable.cpp
  LValue/LValueArrayElement.cpp
  LValue/LValueSimple.cpp
  LValue/ArrayElementLValue.cpp
  LValue/SimpleLValue.cpp
  Method/MethodInvocation.cpp
  Statement/StatementAssert.cpp
  Statement/StatementAssignment.cpp
  Statement/StatementIfFull.cpp
  Statement/StatementIfReduced.cpp
  Statement/StatementMethodInvocation.cpp
  Statement/StatementNewScope.cpp
  Statement/StatementPrint.cpp
  Statement/StatementReturn.cpp
  Statement/StatementVariableDeclaration.cpp
  Statement/StatementWhile.cpp
  Statement/StatementList.cpp
  Type/Type.cpp
  Expression/ExpressionNumber.cpp
  Visitor/TreePrinter.cpp
  Visitor/Interpreter.cpp
  Scopes/TypesScopeLayer.cpp
  Scopes/SymbolTable.cpp
  Functions/Function.cpp
  Functions/FunctionManager.cpp
  Functions/Stack.cpp
  Classes/ClassManager.cpp
  Visitor/FunctionManagerCreator.cpp
  Visitor/TypeChecker.cpp
  Visitor/TypeGetter.cpp
  Core/SizeManager.cpp
  Classes/Class.cpp
  Classes/FieldVisitor.cpp
  Classes/ClassManagerCreator.cpp
)