cmake_minimum_required (VERSION 2.8)

# Create filter by directory in MSVC
macro(source_group_by_dir source_files)
    if(MSVC)
        set(sgbd_cur_dir ${CMAKE_CURRENT_SOURCE_DIR}/../../Src/MirageEngine)
        foreach(sgbd_file ${${source_files}})        
            string(REGEX REPLACE ${sgbd_cur_dir}/ "" sgbd_fpath ${sgbd_file})
            string(REGEX REPLACE "/[^/]*$" "" sgbd_group_name ${sgbd_fpath})
           
            string(COMPARE EQUAL ${sgbd_fpath} ${sgbd_group_name} sgbd_nogroup)
            string(REPLACE "/" "\\" sgbd_group_name ${sgbd_group_name})
            if(sgbd_nogroup)
                set(sgbd_group_name "\\")
            endif(sgbd_nogroup)
            
            source_group(${sgbd_group_name} FILES ${sgbd_file})
        endforeach(sgbd_file)
    endif(MSVC)
endmacro(source_group_by_dir)

# Add director recursively
function(include_sub_directories_recursively root_dir)
    if (IS_DIRECTORY ${root_dir}) # 当前路径是一个目录吗，是的话就加入到包含目录
        include_directories(${root_dir})
    endif()

    file(GLOB ALL_SUB RELATIVE ${root_dir} ${root_dir}/*) # 获得当前目录下的所有文件，让如ALL_SUB列表中
    foreach(sub ${ALL_SUB})
        if (IS_DIRECTORY ${root_dir}/${sub})                    
            include_sub_directories_recursively(${root_dir}/${sub}) # 对子目录递归调用，包含
        endif()
    endforeach()
endfunction()

#------------------------------------------------------------------------------------------------------------

set(CMAKE_INCLUDE_CURRENT_DIR)
SET(CMAKE_CXX_FLAGS "-std=c++0x")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include_directories(.)
include_directories(./Core)

if(MSVC)
    add_definitions(-DUNICODE -D_UNICODE)
    
    include_directories(../../Plugin/Window/Direct3D/include)
    include_directories(../../Plugin/Window/SDL2/include)
    include_directories(../../Plugin/Window/jemalloc/include)
    include_directories(../../Plugin/Window/jemalloc/include/msvc_compat)
    if(CMAKE_CL_64)
        link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../Plugin/Window/Direct3D/lib/x64)
        link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../Plugin/Window/SDL2/lib/x64)
        link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../Plugin/Window/jemalloc/lib/x64)
    else()
        link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../Plugin/Window/Direct3D/lib/x86)
        link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../Plugin/Window/SDL2/lib/x86)
        link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../Plugin/Window/jemalloc/lib/x86)
    endif() 
endif(MSVC)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")  
    find_package(OpenGL REQUIRED)
    find_package(SDL2 REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIRS})
    include_directories(${SDL2_INCLUDE_DIRS})
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../Plugin/Linux/glew-2.1.0/include)  
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../Plugin/Linux/jemalloc/include)  
    if(CMAKE_CL_64)
        link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../Plugin/Linux/jemalloc/lib/64) 
        link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../Plugin/Linux/glew-2.1.0/lib/64)          
    else()

    endif()
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")  

#include_sub_directories_recursively(${CMAKE_CURRENT_SOURCE_DIR}/../../Src/MirageEngine)

file(GLOB_RECURSE project_headers ${CMAKE_CURRENT_SOURCE_DIR}/../../Src/MirageEngine/*.h)
file(GLOB_RECURSE project_cpps ${CMAKE_CURRENT_SOURCE_DIR}/../../Src/MirageEngine/*.cpp)
set(all_files ${project_headers} ${project_cpps})

add_library(me ${all_files})

source_group_by_dir(all_files)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")  
    target_link_libraries(me ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES} libGLEW.a libjemalloc.a)
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux") 
IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
    target_link_libraries(me d3dcompiler.lib SDL2.lib SDL2main.lib SDL2test.lib SDL2.dll d3d11.lib dxgi.lib jemallocso.lib)   

    if(CMAKE_CL_64)
        add_custom_command(TARGET me POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/../../Plugin/Window/SDL2/lib/x64/SDL2.dll" "${CMAKE_CURRENT_BINARY_DIR}")
        add_custom_command(TARGET me POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/../../Plugin/Window/jemalloc/lib/x64/jemallocso.dll" "${CMAKE_CURRENT_BINARY_DIR}")
    else()
        add_custom_command(TARGET me POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/../../Plugin/Window/SDL2/lib/x86/SDL2.dll" "${CMAKE_CURRENT_BINARY_DIR}")
        add_custom_command(TARGET me POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/../../Plugin/Window/jemalloc/lib/x86/jemallocso.dll" "${CMAKE_CURRENT_BINARY_DIR}")
    endif() 
ENDIF(CMAKE_SYSTEM_NAME MATCHES "Windows")