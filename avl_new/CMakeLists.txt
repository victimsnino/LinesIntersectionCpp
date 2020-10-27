set(TARGET avl)

add_library(${TARGET} INTERFACE )

target_include_directories(${TARGET}
INTERFACE
    .
)

if (MSVC)
    add_custom_target(${TARGET}_headers SOURCES avl.h avl_node.h)
endif()

if (UNIT_TESTS)
    add_subdirectory(tests)
endif()
