cmake_minimum_required(VERSION 3.9)
project(test_multi_threaded_sorting)

set(SOURCE_FILES sort_test.cpp)

add_executable(sort_test ${SOURCE_FILES})
target_link_libraries(sort_test catch sort Threads::Threads)

#install(TARGETS sort_test DESTINATION bin)
