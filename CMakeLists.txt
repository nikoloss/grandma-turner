cmake_minimum_required(VERSION 3.7)
project(gtlib VERSION 0.0.1 LANGUAGES C)
include(GNUInstallDirs)
add_library(${PROJECT_NAME} SHARED
        src/gtstack.c
        )
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(${PROJECT_NAME} PROPERTIES
        SOVERSION 0.0.1
        PUBLIC_HEADER "include/gtstack.h;include/gttypes.h"
        )
configure_file(gtlib.pc.in gtlib.pc @ONLY)
install(TARGETS gtlib
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include/gt
        )
install(FILES ${CMAKE_BINARY_DIR}/gtlib.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
