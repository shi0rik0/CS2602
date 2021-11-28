cmake_minimum_required(VERSION 3.20)
project(clion_proj)

set(CMAKE_CXX_STANDARD 14)

enable_testing()

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/source-charset:utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")

add_subdirectory(./oj)

set(GOOGLETEST_VERSION 1.11.0)
add_subdirectory(./external/googletest)

include_directories(./include ./external/googletest/include)

include(GoogleTest)
add_executable(SeqList_test test/SeqList.test.cpp)
target_link_libraries(SeqList_test gtest_main)
add_executable(BST_test test/BST.test.cpp)
target_link_libraries(BST_test gtest_main)
add_executable(Utils_test test/Utils.test.cpp)
target_link_libraries(Utils_test gtest_main)
add_executable(BinTree_test test/bintree.test.cpp)
target_link_libraries(BinTree_test gtest_main)
gtest_discover_tests(SeqList_test BST_test Utils_test BinTree_test)