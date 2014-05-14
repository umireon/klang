cmake_minimum_required(VERSION 2.8)

project(klang)

option(test "Build all tests." OFF)
add_library(parser src/parser.c)

set(serial "0.0.0")

if (test)
    enable_testing()

    set(TESTS OFF CACHE BOOL "")
    add_subdirectory(lib/cpputest)
    file(GLOB TestSourceFiles test/*.cpp)
    add_executable(runUnit ${TestSourceFiles})
    include_directories(${CppUTest_SOURCE_DIR}/include)
    target_link_libraries(runUnit CppUTest CppUTestExt)
    target_link_libraries(runUnit parser)

    add_test(Unit runUnit)

    add_subdirectory(lib/igloo EXCLUDE_FROM_ALL)
    include_directories(${igloo_SOURCE_DIR})
    file(GLOB SpecSourceFiles spec/*.cpp)
    add_executable(runSpec ${SpecSourceFiles})
    target_link_libraries(runSpec parser)

    add_test(Spec runSpec)
endif()
