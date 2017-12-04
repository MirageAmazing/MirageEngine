cmake_minimum_required (VERSION 2.8)

add_compile_options(-std=c++11)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project (Mirage)

# Create filter by directory in MSVC
macro(source_group_by_dir source_files)
    if(MSVC)
        set(sgbd_cur_dir ${CMAKE_CURRENT_SOURCE_DIR})
        foreach(sgbd_file ${${source_files}})           
            string(REGEX REPLACE ${sgbd_cur_dir}/ "" sgbd_fpath ${sgbd_file})
            string(REGEX REPLACE "/[^/]*$" "" sgbd_group_name ${sgbd_fpath})
           
            string(COMPARE EQUAL ${sgbd_fpath} ${sgbd_group_name} sgbd_nogroup)
            string(REPLACE "/" "\\" sgbd_group_name ${sgbd_group_name})
            if(sgbd_nogroup)
                set(sgbd_group_name "\\")
            endif(sgbd_nogroup)

            message(${sgbd_group_name})
            message(${sgbd_file})
            
            source_group(${sgbd_group_name} FILES ${sgbd_file})
        endforeach(sgbd_file)
    endif(MSVC)
endmacro(source_group_by_dir)

# 
function(include_sub_directories_recursively root_dir)
    if (IS_DIRECTORY ${root_dir})               # 当前路径是一个目录吗，是的话就加入到包含目录
        message("include dir: " ${root_dir})
        include_directories(${root_dir})
    endif()

    file(GLOB ALL_SUB RELATIVE ${root_dir} ${root_dir}/*) # 获得当前目录下的所有文件，让如ALL_SUB列表中
    foreach(sub ${ALL_SUB})
        if (IS_DIRECTORY ${root_dir}/${sub})                    
            include_sub_directories_recursively(${root_dir}/${sub}) # 对子目录递归调用，包含
        endif()
    endforeach()
endfunction()

add_subdirectory(./MirageEngine)
add_subdirectory(./EngineTest)