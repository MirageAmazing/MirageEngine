cmake_minimum_required (VERSION 2.8)

add_compile_options(-std=c++11)

include_directories("../MirageEngine")
link_directories("../MirageEngine")

if(MSVC)
    set(ML me)
else()
    add_compile_options(-lpthread)
    set(ML libme.a)
endif()

aux_source_directory(. DIR_SRCS)

add_executable(enginetest ${DIR_SRCS})

if(MSVC)
else()
    target_link_libraries(enginetest pthread)
endif()

target_link_libraries(enginetest ${ML}) 