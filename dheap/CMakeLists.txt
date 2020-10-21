set(TARGET dheap)

add_library(${TARGET} INTERFACE)

target_include_directories(${TARGET}
INTERFACE
    .
)

if (UNIT_TESTS)
    add_subdirectory(tests)
endif()
