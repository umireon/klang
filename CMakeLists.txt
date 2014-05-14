cmake_minimum_required(VERSION 2.8)

project(klang)

option(TEST "Build all tests." OFF)
option(UNIT_TEST "Build unit tests." OFF)
option(INTEGRATION_TEST "Build integration tests." OFF)

set(CTEST_OUTPUT_ON_FAILURE ON)

add_library(parser src/parser.c)

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
    target_link_libraries(runUnit CppUTest CppUTestExt)
    target_link_libraries(runUnit parser)
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
