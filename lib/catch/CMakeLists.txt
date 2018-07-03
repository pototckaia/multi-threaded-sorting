cmake_minimum_required(VERSION 3.9)

project(catch)

set(SOURCE_LIB test.cpp)
add_library(catch STATIC ${SOURCE_LIB})
#install(FILES catch.hpp DESTINATION include)
