add_library(PriorityQueueTests STATIC
        test_priority_q.h
        test_priority_q.cpp
)

set_target_properties(PriorityQueueTests PROPERTIES
        LINKER_LANGUAGE CXX
)

target_include_directories(PriorityQueueTests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)