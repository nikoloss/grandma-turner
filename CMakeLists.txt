cmake_minimum_required(VERSION 3.7)
set(CMAKE_C_FLAGS "${CMAKE_ENABLE_C99}")
set(SOURCE_FILES src/gtstack.c src/gttrie.c src/gtlist.c src/gthashmap.c src/main.c)
set(HEADER_FILES include/gtstack.h include/gttrie.h include/gttypes.h include/gtlist.h include/gthashmap.h)
project(gtlib VERSION 0.0.1 LANGUAGES C)
add_library(${PROJECT_NAME} SHARED
        src/gtstack.c
		src/gttrie.c
        src/gtlist.c)
set_target_properties(${PROJECT_NAME} PROPERTIES
        SOVERSION 0.0.1
        PUBLIC_HEADER "${HEADER_FILES}"
	)

add_executable(gtexe ${HEADER_FILES} ${SOURCE_FILES})
#configure_file(gtlib.pc.in gtlib.pc @ONLY)
#install(TARGETS gtlib
#        LIBRARY DESTINATION lib
#        PUBLIC_HEADER DESTINATION include/gt
#        )
#install(FILES ${CMAKE_BINARY_DIR}/gtlib.pc
#        DESTINATION lib/pkgconfig)
#
##通过pkg-config获得criterion
##find_library(UNITTEST criterion)
#find_package(PkgConfig)
#pkg_check_modules(UNITTEST criterion)
#
#
##如果成功获取criterion说明机器是安装了criterion
#if (UNITTEST_FOUND)
#    set(CMAKE_BUILD_TYPE Debug)
#    enable_testing()
#    #设置单元测试的源码目录
#    set(UNITTEST_SOURCE  test/test_gttrie.c test/test_gtstack.c test/test_gtlist.c include/gthashmap.h src/gthashmap.c test/test_gthashmap.c)
#    #打印一些信息 提示用户在make之后执行make test就是单元测试
#    message("-- be ready to run test case, usage: make && make test")
#    #把所有的测试源码编译成可执行文件runtest
#    add_executable(runtest ${UNITTEST_SOURCE} ${HEADER_FILES} ${SOURCE_FILES})
#    #执行runtest需要criterion库依赖
#    target_link_libraries(runtest ${UNITTEST_LIBRARIES})
#    add_test(runtest runtest)
#endif (UNITTEST_FOUND)
