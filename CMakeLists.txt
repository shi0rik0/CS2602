cmake_minimum_required(VERSION 3.20)
project(clion_proj)

set(CMAKE_CXX_STANDARD 14)

enable_testing()

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/source-charset:utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")
add_executable(clion_proj ./src/_Main.cpp)

set(GOOGLETEST_VERSION 1.11.0)
add_subdirectory(./external/googletest)

include_directories(./include ./external/googletest/include)

add_executable(SeqList_test test/SeqList_test.cpp)
target_link_libraries(SeqList_test gtest_main)
include(GoogleTest)
gtest_discover_tests(SeqList_test)