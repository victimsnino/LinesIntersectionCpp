set(TARGET dheap_tests)

add_executable(${TARGET}
    dheap_tests.cpp
)

target_link_libraries(${TARGET} dheap catch)
SET_TARGET_PROPERTIES(${TARGET} PROPERTIES FOLDER "Tests")