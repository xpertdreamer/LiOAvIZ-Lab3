add_library(StackTests STATIC
        test_stack.cpp
        test_stack.h
)

set_target_properties(StackTests PROPERTIES
        LINKER_LANGUAGE CXX
)

target_include_directories(StackTests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)