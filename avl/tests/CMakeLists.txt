set(TARGET avl_tests)

add_executable(${TARGET}
    avl_tests.cpp
)

target_link_libraries(${TARGET} avl catch)
SET_TARGET_PROPERTIES(${TARGET} PROPERTIES FOLDER "Tests")