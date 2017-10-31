aux_source_directory(. Core_DIR_SRCS)

add_subdirectory(Allocator)
add_subdirectory(HAL)
add_subdirectory(Math)

add_library(CoreLib ${Core_DIR_SRCS})

target_link_libraries(CoreLib AllocatorLib)
target_link_libraries(CoreLib HALLib)
target_link_libraries(CoreLib MathLib)