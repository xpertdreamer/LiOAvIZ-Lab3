add_library(Stack STATIC
        stack.h
)

set_target_properties(Stack PROPERTIES
        LINKER_LANGUAGE CXX
)

target_include_directories(Stack PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)