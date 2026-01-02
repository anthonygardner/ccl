cmake_minimum_required(VERSION 3.15...4.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
    CppLibraryTemplate
    VERSION 0.0.1
    DESCRIPTION "C++ library template"
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
    mylib
    src/mylib.cpp
)

target_include_directories(
    mylib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(BUILD_PYTHON_API)
    pybind11_add_module(
        _mylib
        src/python.cpp
    )

    target_link_libraries(_mylib PRIVATE mylib)

    set_target_properties(
        _mylib PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/python/mylib/
    )
endif()

if(BUILD_CXX_TESTS)
    enable_testing()

    add_executable(
        mylib_test
        tests/test.cpp
    )

    target_link_libraries(
        mylib_test PRIVATE
        mylib
        GTest::gtest_main
    )

    include(GoogleTest)

    gtest_discover_tests(mylib_test)
endif()