cmake_minimum_required (VERSION 2.8)

set(CMAKE_CXX_COMPLIER,             "/usr/lib/llvm-3.6/bin/clang++")
set(CMAKE_CXX_FLAGS,                "-std=c++11")
SET (CMAKE_CXX_FLAGS_DEBUG          "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
SET (CMAKE_AR      "/usr/bin/llvm-ar-3.6")
SET (CMAKE_LINKER  "/usr/bin/llvm-ld-3.6")
SET (CMAKE_NM      "/usr/bin/llvm-nm-3.6")
SET (CMAKE_OBJDUMP "/usr/bin/llvm-objdump-3.6")
SET (CMAKE_RANLIB  "/usr/bin/llvm-ranlib-3.6")

find_library(ML MirageEngineLib ../MirageEngine NO_DEFAULT_PATH)
link_libraries(${ML})

project (EngineTest)

aux_source_directory(. DIR_SRCS)

add_executable(EngineTest ${DIR_SRCS})

target_link_libraries(EngineTest ${ML})