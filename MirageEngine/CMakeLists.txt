cmake_minimum_required (VERSION 2.8)

set(CMAKE_INCLUDE_CURRENT_DIR)
add_compile_options(-std=c++11)

aux_source_directory(./Core/Allocator Srcs_Allocator)
aux_source_directory(./Core/HAL Srcs_HAL)
aux_source_directory(./Core/Math Srcs_Math)

add_library(me ${Srcs_Allocator} ${Srcs_HAL} ${Srcs_Math})

include_sub_directories_recursively(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE project_headers *.h)
file(GLOB_RECURSE project_cpps *.cpp)
set(all_files ${project_headers} ${project_cpps})
source_group_by_dir(all_files)

source_group("Include" FILES ./Core/HAL/IOBase.h)