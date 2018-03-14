cmake_minimum_required(VERSION 3.7)

set(SOURCE_FILES src/gtstack.c src/gttrie.c)
set(HEADER_FILES include/gttypes.h include/gtstack.h include/gttrie.h)
project(gtlib VERSION 0.0.1 LANGUAGES C)
add_library(${PROJECT_NAME} SHARED
        src/gtstack.c
		src/gttrie.c)
set_target_properties(${PROJECT_NAME} PROPERTIES
        SOVERSION 0.0.1
        PUBLIC_HEADER ${HEADER_FILES}
	)
configure_file(gtlib.pc.in gtlib.pc @ONLY)
install(TARGETS gtlib
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include/gt
        )
install(FILES ${CMAKE_BINARY_DIR}/gtlib.pc
        DESTINATION lib/pkgconfig)

find_package(PkgConfig)
pkg_check_modules(UNITTEST criterion)

if (UNITTEST_FOUND)
    set(UNITTEST_SOURCE test/test_gtstack.c test/test_gttrie.c)
    enable_testing()
    message("-- be ready to run test case, usage: make && make test")
    add_executable(runtest ${UNITTEST_SOURCE} ${HEADER_FILES} ${SOURCE_FILES})
    target_link_libraries(runtest ${UNITTEST_LIBRARIES})
    add_test(runtest runtest)
endif (UNITTEST_FOUND)
