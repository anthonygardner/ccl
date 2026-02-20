cmake_minimum_required(VERSION 3.15...4.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

project(
    ccl
    VERSION 0.0.1
    DESCRIPTION "Common Control Library (CCL)"
    LANGUAGES C CXX
)

option(BUILD_PYTHON_API "Build Python API using pybind11" ON)
option(BUILD_CXX_TESTS "Build C++ unit tests" ON)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG v2.12.0
)

FetchContent_Declare(
    utest
    GIT_REPOSITORY https://github.com/sheredom/utest.h.git
    GIT_TAG master
)

FetchContent_MakeAvailable(googletest pybind11 utest)

add_library(
    ccl
    cpp/src/ccl.cpp
    cpp/src/complementary_filter.cpp
    cpp/src/pid.cpp
)

target_include_directories(
    ccl PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/cpp/include/
)

add_library(
    ccl_core
    core/src/pid.c
)

target_include_directories(
    ccl_core
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/core/include/
)

target_link_libraries(
    ccl
    PUBLIC
    ccl_core
)

add_executable(
    ccl_core_test 
    tests/core/main.c
    tests/core/test_pid.c
)

target_include_directories(
    ccl_core_test 
    PRIVATE 
    ${utest_SOURCE_DIR}
)

target_link_libraries(
    ccl_core_test 
    PRIVATE 
    ccl_core
)

add_executable(
    complementary_filter_demo 
    demos/complementary_filter.cpp
)

target_link_libraries(
    complementary_filter_demo 
    ccl
)

if(BUILD_PYTHON_API)
    pybind11_add_module(
        _ccl
        python/bindings.cpp
    )

    target_link_libraries(
        _ccl 
        PRIVATE 
        ccl
    )

    set_target_properties(
        _ccl 
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/python/ccl/
    )
endif()

if(BUILD_CXX_TESTS)
    enable_testing()

    add_executable(
        ccl_test
        tests/cpp/ccl_test.cpp
        tests/cpp/complementary_filter_test.cpp
        tests/cpp/pid_test.cpp
    )

    target_link_libraries(
        ccl_test 
        PRIVATE
        ccl
        GTest::gtest_main
    )

    include(GoogleTest)

    gtest_discover_tests(ccl_test)
endif()