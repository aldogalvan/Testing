cmake_minimum_required(VERSION 3.1)
project(tetgen)

add_library(tetgen STATIC tetgen.cxx predicates.cxx)
target_compile_definitions(tetgen PRIVATE -DTETLIBRARY)

set_target_properties(tetgen PROPERTIES POSITION_INDEPENDENT_CODE ON)
