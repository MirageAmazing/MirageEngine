aux_source_directory(. Core_Math_DIR_SRCS)
message([STATUS],${Core_Math_DIR_SRCS})
add_library(MathLib ${Core_Math_DIR_SRCS})