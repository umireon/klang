cmake_minimum_required(VERSION 2.8)

project(klang)

option(TEST "Build all tests." OFF)
option(UNIT_TEST "Build unit tests." OFF)
option(INTEGRATION_TEST "Build integration tests." OFF)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIR})

file(GLOB PARSER_SRC "${CMAKE_SOURCE_DIR}/src/parser/*" "${CMAKE_SOURCE_DIR}/include/parser.h")
file(GLOB KOBJECT_SRC "${CMAKE_SOURCE_DIR}/src/kobject/*" "${CMAKE_SOURCE_DIR}/include/kobject.h")
file(GLOB AST_SRC "${CMAKE_SOURCE_DIR}/src/ast/*" "${CMAKE_SOURCE_DIR}/include/ast.h")
file(GLOB KFUNC_SRC "${CMAKE_SOURCE_DIR}/src/kfunc/*" "${CMAKE_SOURCE_DIR}/include/kfunc/*.h")

add_library(kobject ${KOBJECT_SRC})

add_library(ast ${AST_SRC})
target_link_libraries(ast kobject)

add_library(parser ${PARSER_SRC})
target_link_libraries(parser ast)

add_library(kfunc ${KFUNC_SRC})
target_link_libraries(kfunc kobject)

include_directories("${CMAKE_SOURCE_DIR}/include")

add_executable(print_ast src/print_ast.cpp)
target_link_libraries(print_ast parser kobject ast kfunc)
target_link_libraries(print_ast ${Boost_LIBRARIES})

add_executable(ast_calc src/ast_calc.cpp)
target_link_libraries(ast_calc parser kobject ast kfunc)
target_link_libraries(ast_calc ${Boost_LIBRARIES})

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
    add_library(parser_test ${PARSER_SRC})
    add_library(kobject_test ${KOBJECT_SRC})
    add_library(ast_test ${AST_SRC})
    add_library(kfunc_test ${KFUNC_SRC})
    set_target_properties(parser_test PROPERTIES COMPILE_FLAGS "-include ${CMAKE_SOURCE_DIR}/test/test_helper.h")
    set_target_properties(kobject_test PROPERTIES COMPILE_FLAGS "-include ${CMAKE_SOURCE_DIR}/test/test_helper.h")
    set_target_properties(ast_test PROPERTIES COMPILE_FLAGS "-include ${CMAKE_SOURCE_DIR}/test/test_helper.h")
    set_target_properties(kfunc_test PROPERTIES COMPILE_FLAGS "-include ${CMAKE_SOURCE_DIR}/test/test_helper.h")

    add_executable(runUnit ${TestSourceFiles})
    target_compile_options(runUnit PUBLIC "-include" "${CMAKE_SOURCE_DIR}/test/test_helper.h")
    target_link_libraries(runUnit ${Boost_LIBRARIES})
    target_link_libraries(runUnit CppUTest CppUTestExt)
    target_link_libraries(runUnit parser_test ast_test kobject_test kfunc_test)

    add_test(Unit runUnit)
endif ()

if (INTEGRATION_TEST)
    enable_testing()

    add_subdirectory(vendors/igloo EXCLUDE_FROM_ALL)
    include_directories(${igloo_SOURCE_DIR})

    file(GLOB SpecSourceFiles spec/*.cpp)
    add_executable(runSpec ${SpecSourceFiles})
    target_link_libraries(runSpec parser kobject ast kfunc)
    target_link_libraries(runSpec ${Boost_LIBRARIES})
    add_test(Spec runSpec)
endif ()
