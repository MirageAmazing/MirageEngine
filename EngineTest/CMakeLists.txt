cmake_minimum_required (VERSION 2.8)

add_compile_options(-std=c++11)

find_library(ML libme ../MirageEngine NO_DEFAULT_PATH)
link_libraries(${ML})

project (EngineTest)

aux_source_directory(. DIR_SRCS)

add_executable(enginetest ${DIR_SRCS})

target_link_libraries(enginetest ${ML})