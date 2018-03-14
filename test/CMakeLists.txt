add_executable(firsttest firsttest.c)
target_link_libraries(firsttest ${TESTUNIT_LIBRARIES})
add_test(firsttest firsttest)
