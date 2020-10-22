cmake_minimum_required(VERSION 3.10)

project(Lines_Intersection C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

SET(UNIT_TESTS ON)

enable_testing()

add_subdirectory(catch EXCLUDE_FROM_ALL)
add_subdirectory(dheap)
add_subdirectory(avl)