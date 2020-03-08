cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME MiniJavaArithmeticalInterpreter)

project(${PROJECT_NAME})

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

BISON_TARGET(
    Parser
    parser.y
    ${${PROJECT_NAME}_SOURCE_DIR}/parser.cpp
    DEFINES_FILE ${${PROJECT_NAME}_SOURCE_DIR}/parser.h
)

FLEX_TARGET(
    Scanner
    scanner.l
    ${${PROJECT_NAME}_SOURCE_DIR}/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

add_executable(
    ${PROJECT_NAME}
    main.cpp
    driver.cpp
    ${BISON_Parser_OUTPUTS}
    ${FLEX_Scanner_OUTPUTS}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_SOURCE_DIR})
