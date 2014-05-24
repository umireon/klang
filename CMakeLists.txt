cmake_minimum_required(VERSION 2.8)

project(klang)

option(TEST "Build all tests." OFF)
option(UNIT_TEST "Build unit tests." OFF)
option(INTEGRATION_TEST "Build integration tests." OFF)

set(PARSER_SRC src/parser.cpp src/ast.cpp src/ParseNumber.cpp src/ParseTerm.cpp)
add_library(parser ${PARSER_SRC})

add_executable(print_ast src/print_ast.cpp)
target_link_libraries(print_ast parser)

add_executable(ast_calc src/ast_calc.cpp)
target_link_libraries(ast_calc parser)

add_executable(ast_compile src/ast_compile.cpp)
target_link_libraries(ast_compile parser)

set(serial "0.0.0")

if (TEST)
    set(UNIT_TEST ON)
    set(INTEGRATION_TEST ON)
endif()

if (UNIT_TEST)
    enable_testing()

    add_subdirectory(lib/cpputest EXCLUDE_FROM_ALL)
    include_directories(${CppUTest_SOURCE_DIR}/include)

    file(GLOB TestSourceFiles test/*.cpp)
    add_executable(runUnit ${TestSourceFiles})
    set_target_properties(runUnit PROPERTIES COMPILE_FLAGS "-include ${CMAKE_SOURCE_DIR}/test/test_helper.h")
    add_library(parser_test ${PARSER_SRC})
    set_target_properties(parser_test PROPERTIES COMPILE_FLAGS "-include ${CMAKE_SOURCE_DIR}/test/test_helper.h")
    target_link_libraries(runUnit CppUTest CppUTestExt)
    target_link_libraries(runUnit parser_test)
    add_test(Unit runUnit)
endif()

if (INTEGRATION_TEST)
    enable_testing()

    add_subdirectory(lib/igloo EXCLUDE_FROM_ALL)
    include_directories(${igloo_SOURCE_DIR})

    file(GLOB SpecSourceFiles spec/*.cpp)
    add_executable(runSpec ${SpecSourceFiles})
    target_link_libraries(runSpec parser)
    add_test(Spec runSpec)
endif()
