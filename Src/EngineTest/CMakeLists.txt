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

file(GLOB_RECURSE project_headers *.h)
file(GLOB_RECURSE project_cpps *.cpp)
set(all_files ${project_headers} ${project_cpps})

add_executable(enginetest ${all_files})

if(MSVC)
else()
    target_link_libraries(enginetest pthread)
endif()

target_link_libraries(enginetest ${ML}) 

source_group_by_dir(all_files)