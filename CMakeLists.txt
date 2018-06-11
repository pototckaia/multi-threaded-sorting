cmake_minimum_required(VERSION 3.9)
project(multi_threaded_sorting)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall")

add_executable(sort_benchmark sort_benchmark.cpp dump.h sort.h)
#target_link_libraries (sort_benchmark ${CMAKE_THREAD_LIBS_INIT})
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(sort_benchmark benchmark Threads::Threads)


SET(CATCH_PATH /home/oem/Documents/Homeworks/Cpp-homework/catch)
add_library(catch STATIC IMPORTED)
set_property(TARGET catch PROPERTY IMPORTED_LOCATION "${CATCH_PATH}/libcatch.a")

add_executable(sort_test sort_test.cpp dump.h sort.h)
target_include_directories(sort_test PRIVATE ${CATCH_PATH})
target_link_libraries(sort_test catch Threads::Threads)

