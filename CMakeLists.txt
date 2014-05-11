cmake_minimum_required(VERSION 2.8)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(cotire)

set(CMAKE_CXX_FLAGS "-fextended-identifiers")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

project(test)

option(test "Build all tests." ON)

set(serial "0.0.0")

add_library(add src/add.c)
add_executable(calc main.c)
target_link_libraries(calc add)

if (test)
    enable_testing()

    add_subdirectory(lib/cpputest)
    file(GLOB TestSourceFiles test/*.cpp)
    add_executable(runUnit ${TestSourceFiles})
    include_directories(${CppUTest_SOURCE_DIR}/include)
    target_link_libraries(runUnit CppUTest CppUTestExt)
    target_link_libraries(runUnit add)

    add_test(Unit runUnit)

    add_subdirectory(lib/igloo)
    include_directories(${igloo_SOURCE_DIR})
    file(GLOB SpecSourceFiles spec/*.cpp)
    add_executable(runSpec ${SpecSourceFiles})
    target_link_libraries(runSpec add)

    add_test(Spec runSpec)
endif()
