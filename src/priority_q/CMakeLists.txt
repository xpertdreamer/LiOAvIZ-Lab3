add_library(PriorityQueue STATIC
        priority_q.h
)

set_target_properties(PriorityQueue PROPERTIES
        LINKER_LANGUAGE CXX
)

target_include_directories(PriorityQueue PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)

