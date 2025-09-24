add_library(Utils STATIC
        utils.cpp
        utils.h
)

set_target_properties(Utils PROPERTIES
        LINKER_LANGUAGE CXX
)

target_include_directories(Utils PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)