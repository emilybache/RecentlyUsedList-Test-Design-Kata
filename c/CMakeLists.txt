cmake_minimum_required(VERSION 3.16)
set(CMAKE_VERBOSE_MAKEFILE ON)
project(RecentlyUsedList VERSION 1.0
        DESCRIPTION "Improve the tests."
        LANGUAGES CXX)

# uncomment these lines to enable coverage measurements using gcov
#set(CMAKE_CXX_FLAGS "--coverage")

enable_testing()
add_subdirectory(src)
add_subdirectory(test-doctest)
add_subdirectory(test-gtest)

