cmake_minimum_required(VERSION 3.15...4.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
    ccl
    VERSION 0.0.1
    DESCRIPTION "Common Control Library (CCL)"
    LANGUAGES CXX
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

FetchContent_MakeAvailable(googletest pybind11)

add_library(
    ccl
    src/ccl.cpp
    src/complementary_filter.cpp
    src/pid.cpp
    src/uart.cpp
)

target_include_directories(
    ccl PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(complementary_filter_demo demos/complementary_filter_demo.cpp)
target_link_libraries(complementary_filter_demo ccl)

if(BUILD_PYTHON_API)
    pybind11_add_module(
        _ccl
        src/python.cpp
    )

    target_link_libraries(_ccl PRIVATE ccl)

    set_target_properties(
        _ccl PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/python/ccl/
    )
endif()

if(BUILD_CXX_TESTS)
    enable_testing()

    add_executable(
        ccl_test
        tests/ccl_test.cpp
        tests/complementary_filter_test.cpp
        tests/pid_test.cpp
    )

    target_link_libraries(
        ccl_test PRIVATE
        ccl
        GTest::gtest_main
    )

    include(GoogleTest)

    gtest_discover_tests(ccl_test)
endif()