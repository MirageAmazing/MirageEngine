cmake_minimum_required (VERSION 2.8)

add_compile_options(-std=c++11)

aux_source_directory(./Core/Allocator Srcs_Allocator)
aux_source_directory(./Core/HAL Srcs_HAL)
aux_source_directory(./Core/Math Srcs_Math)

add_library(me ${Srcs_Allocator} ${Srcs_HAL} ${Srcs_Math})

target_link_libraries(me MathLib)