set(TARGET intersection_utils)

add_library(${TARGET} STATIC 
    intersection_utils.cpp 
    intersection_utils.h)

target_include_directories(${TARGET}
PUBLIC
    .
)

if (UNIT_TESTS)
    add_subdirectory(tests)
endif()
