cmake_minimum_required (VERSION 2.8)

add_compile_options(-std=c++11)

project (mirageengine)

aux_source_directory(. DIR_SRCS_B)

add_subdirectory(Core/Math)

add_library(me ${DIR_SRCS_B})

target_link_libraries(me MathLib)