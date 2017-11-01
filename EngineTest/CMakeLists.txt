cmake_minimum_required (VERSION 2.8)

add_compile_options(-std=c++11)
add_compile_options(-lpthread)

project (EngineTest)

aux_source_directory(. DIR_SRCS)

add_executable(enginetest ${DIR_SRCS})

find_library(ML libme.a ../MirageEngine)
target_link_libraries(enginetest ${ML}) 
target_link_libraries(enginetest pthread) 