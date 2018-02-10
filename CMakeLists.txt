cmake_minimum_required(VERSION 3.7)
#set(CMAKE_INSTALL_PREFIX /usr)
project(gtlib VERSION 0.0.1 LANGUAGES C)
add_library(${PROJECT_NAME} SHARED
        src/gtstack.c
		src/gttrie.c)
set_target_properties(${PROJECT_NAME} PROPERTIES
        SOVERSION 0.0.1
        PUBLIC_HEADER "include/gtstack.h;\
include/gttypes.h;\
include/gttrie.h"
	)
configure_file(gtlib.pc.in gtlib.pc @ONLY)
install(TARGETS gtlib
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include/gt
        )
install(FILES ${CMAKE_BINARY_DIR}/gtlib.pc
        DESTINATION lib/pkgconfig)
