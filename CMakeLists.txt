cmake_minimum_required(VERSION 2.8)

project(klang)

option(TEST "Build all tests." OFF)
option(UNIT_TEST "Build unit tests." OFF)
option(INTEGRATION_TEST "Build integration tests." OFF)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIR})

file(GLOB PARSER_SRC "${CMAKE_SOURCE_DIR}/src/parser/*" "${CMAKE_SOURCE_DIR}/include/parser.h")
file(GLOB KOBJECT_SRC "${CMAKE_SOURCE_DIR}/src/kobject/*" "${CMAKE_SOURCE_DIR}/include/kobject.h")
file(GLOB_RECURSE AST_SRC "${CMAKE_SOURCE_DIR}/src/ast/*" "${CMAKE_SOURCE_DIR}/include/ast/*")
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

if (KLANG_UNIT)
    enable_testing()

    set(TEST_HELPER_H "${CMAKE_SOURCE_DIR}/test/test_helper.h")
    set(CLANG_UNIT_COMPILE_FLAGS "-include ${TEST_HELPER_H}")

    if (KLANG_COVERAGE)
        set(CLANG_UNIT_COMPILE_FLAGS "${CLANG_UNIT_COMPILE_FLAGS} -coverage")
    endif ()

    set(TESTS OFF CACHE BOOL "CppUTest test")
    add_subdirectory(vendors/cpputest)
    include_directories(${CppUTest_SOURCE_DIR}/include)

    file(GLOB TestSourceFiles test/*_test.cpp)

    add_executable(runUnit ${TestSourceFiles} test/test_runner.cpp)
    target_link_libraries(runUnit ${Boost_LIBRARIES})
    target_link_libraries(runUnit CppUTest CppUTestExt)
    target_link_libraries(runUnit parser ast kobject kfunc)
    set_target_properties(runUnit PROPERTIES COMPILE_FLAGS ${CLANG_UNIT_COMPILE_FLAGS})
    set_target_properties(runUnit PROPERTIES LINK_FLAGS ${CLANG_UNIT_COMPILE_FLAGS})

    target_link_libraries(parser CppUTest CppUTestExt)
    target_link_libraries(ast CppUTest CppUTestExt)
    target_link_libraries(kobject CppUTest CppUTestExt)
    target_link_libraries(kfunc CppUTest CppUTestExt)
    set_target_properties(parser ast kobject kfunc PROPERTIES COMPILE_FLAGS ${CLANG_UNIT_COMPILE_FLAGS})
    set_target_properties(parser ast kobject kfunc PROPERTIES LINK_FLAGS ${CLANG_UNIT_COMPILE_FLAGS})

    set_target_properties(ast_calc ast_compile print_ast PROPERTIES LINK_FLAGS ${CLANG_UNIT_COMPILE_FLAGS})

    add_test(Unit runUnit)
endif ()

