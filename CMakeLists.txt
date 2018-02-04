cmake_minimum_required(VERSION 3.7)
set(CMAKE_INSTALL_PREFIX /usr)
project(gtlib VERSION 0.0.1 LANGUAGES C)
include(GNUInstallDirs)
add_library(${PROJECT_NAME} SHARED
        src/gtstack.c
        )
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(${PROJECT_NAME} PROPERTIES
        SOVERSION 0.0.1
        PUBLIC_HEADER "include/gtstack.h;include/gttypes.h"
#	INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib"
	)
#SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
#SET(CMAKE_SKIP_BUILD_RPATH FALSE)
#SET(CMAKE_BUILD_WITH_INSTLL_RPATH FALSE)
#SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
configure_file(gtlib.pc.in gtlib.pc @ONLY)
install(TARGETS gtlib
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include/gt
        )
install(FILES ${CMAKE_BINARY_DIR}/gtlib.pc
        DESTINATION lib/pkgconfig)
