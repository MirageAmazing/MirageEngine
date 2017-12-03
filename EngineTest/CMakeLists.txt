cmake_minimum_required (VERSION 2.8)

add_compile_options(-std=c++11)
add_compile_options(-lpthread)

link_directories("../MirageEngine")
set(ML libme.a)
message(${ML})

aux_source_directory(. DIR_SRCS)

add_executable(enginetest ${DIR_SRCS})

target_link_libraries(enginetest pthread)
target_link_libraries(enginetest ${ML}) 