cmake_minimum_required(VERSION 3.9)
project(benchmark_multi_threaded_sorting)

set(SOURCE_FILES sort_benchmark.cpp)

add_executable(sort_benchmark ${SOURCE_FILES})
target_link_libraries(sort_benchmark sort benchmark Threads::Threads)

#install(TARGETS sort_benchmark DESTINATION bin)