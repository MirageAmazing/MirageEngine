cmake_minimum_required (VERSION 2.8)

set(CMAKE_INCLUDE_CURRENT_DIR)
add_compile_options(-std=c++11)

include_sub_directories_recursively(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE project_headers *.h)
file(GLOB_RECURSE project_cpps *.cpp)
set(all_files ${project_headers} ${project_cpps})

add_library(me ${all_files})

source_group_by_dir(all_files)
