cmake_minimum_required (VERSION 2.6)
project (leptjson_test C)

if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    # set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi -pedantic -Wall")
    # 使用c99标准以支持//注释格式
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall")
endif()

add_library(leptjson leptjson.c) # 在不指定STATIC还是SHARED的情况下,默认生成静态库.a文件
add_definitions(-DSOLUTION) # 是否要以SOLUTION模式编译
add_executable(leptjson_test test.c)
target_link_libraries(leptjson_test leptjson)
