add_library(QueueTests STATIC
        test_queue.cpp
        test_queue.h
)

set_target_properties(QueueTests PROPERTIES
        LINKER_LANGUAGE CXX
)

target_include_directories(QueueTests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)