set(TARGET dheap)

add_library(${TARGET} INTERFACE )

target_include_directories(${TARGET}
INTERFACE
    .
)

if (MSVC)
    add_custom_target(${TARGET}_headers SOURCES dheap.h dheap_utils.h)
    SET_TARGET_PROPERTIES(${TARGET}_headers PROPERTIES FOLDER "Headers")
endif()

if (UNIT_TESTS)
    add_subdirectory(tests)
endif()
