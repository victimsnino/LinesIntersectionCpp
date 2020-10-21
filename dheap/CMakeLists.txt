set(TARGET dheap)

add_library(${TARGET} STATIC dheap.h dheap_utils.h)

target_include_directories(${TARGET}
PUBLIC
    .
)

set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE CXX)

if (UNIT_TESTS)
    add_subdirectory(tests)
endif()
