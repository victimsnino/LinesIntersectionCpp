set(TARGET benchmark)

add_executable(${TARGET}
    benchmark.cpp
    
    utils.h)

target_link_libraries(${TARGET} avl dheap intersection_utils)