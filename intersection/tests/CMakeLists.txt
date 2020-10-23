set(TARGET intersection_tests)

add_executable(${TARGET}
intersection_tests.cpp
)

target_link_libraries(${TARGET} avl dheap intersection_utils catch)
SET_TARGET_PROPERTIES(${TARGET} PROPERTIES FOLDER "Tests")

add_test(${TARGET} ${TARGET})