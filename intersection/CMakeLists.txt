set(TARGET intersection_utils)

add_library(${TARGET} STATIC 
    intersection_utils.cpp 
    intersection_utils.h)

target_include_directories(${TARGET}
PUBLIC
    .
)
target_link_libraries(${TARGET} PUBLIC avl dheap)

if (UNIT_TESTS)
    add_subdirectory(tests)
endif()
