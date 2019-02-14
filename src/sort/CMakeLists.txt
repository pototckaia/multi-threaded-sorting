cmake_minimum_required(VERSION 3.9)
project(multi_sort)

set(SOURCE_FILES dump.h dump.cpp sort.h sort.cpp)

add_library(sort SHARED STATIC ${SOURCE_FILES})
target_link_libraries(sort glog::glog)


install(FILES dump.h sort.h DESTINATION include/sort)
install(TARGETS sort DESTINATION lib)
