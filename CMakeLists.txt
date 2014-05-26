cmake_minimum_required(VERSION 2.8)

project(klang)

option(TEST "Build all tests." OFF)
option(UNIT_TEST "Build unit tests." OFF)
option(INTEGRATION_TEST "Build integration tests." OFF)

file(GLOB PARSER_SRC "${CMAKE_SOURCE_DIR}/src/parser/*")
add_library(parser ${PARSER_SRC})
include_directories("${CMAKE_SOURCE_DIR}/src")

add_executable(print_ast src/print_ast.cpp)
target_link_libraries(print_ast parser)

add_executable(ast_calc src/ast_calc.cpp)
target_link_libraries(ast_calc parser)

if (MSVC)
    add_subdirectory(vendors/wineditline)
    target_link_libraries(ast_calc edit_static)
    include_directories(${WinEditLine_SOURCE_DIR}/include)
else ()
    target_link_libraries(ast_calc edit)
endif ()

add_executable(ast_compile src/ast_compile.cpp)
target_link_libraries(ast_compile parser)

set(serial "0.0.0")

if (TEST)
    set(UNIT_TEST ON)
    set(INTEGRATION_TEST ON)
endif ()

if (UNIT_TEST)
    enable_testing()

    set(TESTS OFF CACHE BOOL "CppUTest test")
    add_subdirectory(vendors/cpputest)
    include_directories(${CppUTest_SOURCE_DIR}/include)

    file(GLOB TestSourceFiles test/*.cpp)
    add_executable(runUnit ${TestSourceFiles})
    set_target_properties(runUnit PROPERTIES COMPILE_FLAGS "-include ${CMAKE_SOURCE_DIR}/test/test_helper.h")
    add_library(parser_test ${PARSER_SRC})
    set_target_properties(parser_test PROPERTIES COMPILE_FLAGS "-include ${CMAKE_SOURCE_DIR}/test/test_helper.h")
    target_link_libraries(runUnit CppUTest CppUTestExt)
    target_link_libraries(runUnit parser_test)
    add_test(Unit runUnit)
endif ()

if (INTEGRATION_TEST)
    enable_testing()

    add_subdirectory(vendors/igloo EXCLUDE_FROM_ALL)
    include_directories(${igloo_SOURCE_DIR})

    file(GLOB SpecSourceFiles spec/*.cpp)
    add_executable(runSpec ${SpecSourceFiles})
    target_link_libraries(runSpec parser)
    add_test(Spec runSpec)
endif ()
