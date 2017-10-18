cmake_minimum_required (VERSION 2.8)

project (MirageEngineLib)

aux_source_directory(./Allocator DIR_SRCS)

add_subdirectory(Core)

add_library(MirageEngineLib ${DIR_SRCS})

target_link_libraries(MirageEngineLib CoreLib)