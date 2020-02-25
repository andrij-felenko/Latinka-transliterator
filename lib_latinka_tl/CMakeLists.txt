cmake_minimum_required(VERSION 3.14)
project(lib_latinka_tl)

add_library(lib_latinka_tl latinkaConverter.cpp include/lib_latinka_tl/latinkaConverter.h)

set_target_properties(lib_latinka_tl PROPERTIES OUTPUT_NAME "latinkaTranslitterator")
target_link_libraries(lib_latinka_tl)
target_include_directories(lib_latinka_tl
    PUBLIC  include
    PRIVATE include/lib_latinka_tl
)
