cmake_minimum_required(VERSION 3.17)
project(DDD_Demo_For_C++)
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

set(CMAKE_CXX_STANDARD 14)
# Prevent overriding the parent project's compiler/linker
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#添加头文件搜索路径
include_directories(/usr/local/include)
#添加库文件搜索路径
link_directories(/usr/local/lib)
# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)
add_library(staticInit_commandBus src/框架组件/命令总线/命令总线.cpp)
add_library(staticInit_event src/框架组件/事件总线/事件发布订阅服务.cpp)
add_library(staticInit_sington src/框架组件/命名服务/静态初始化.cpp)
add_executable(infrastructureTest test/框架测试/基础框架测试.cpp)

add_library(staticInit_user src/用户BC/静态初始化.cpp)
add_library(staticInit_userUnitTest test/单元测试/用户BC/静态初始化.cpp)
add_executable(userUnitTest test/单元测试/用户BC/单元测试.cpp)

add_library(staticInit_fund src/资金帐户BC/静态初始化.cpp)
add_library(staticInit_fundUnitTest test/单元测试/资金帐户BC/静态初始化.cpp)
add_executable(fundUnitTest test/单元测试/资金帐户BC/单元测试.cpp)

add_library(staticInit_transfer src/转账BC/静态初始化.cpp)
add_library(staticInit_transferUnitTest test/单元测试/转账BC/静态初始化.cpp)
add_executable(tansferUnitTest test/单元测试/转账BC/单元测试.cpp)

add_executable(tansferFlowTest test/集成测试/转账流程测试.cpp)

target_link_libraries(infrastructureTest
        gtest_main
        staticInit_event
        staticInit_sington
        staticInit_commandBus
)
target_link_libraries(userUnitTest
        gtest_main
        staticInit_event
        staticInit_sington
        staticInit_user
        staticInit_userUnitTest)
target_link_libraries(tansferUnitTest
        gtest_main
        staticInit_event
        staticInit_sington
        staticInit_commandBus
        staticInit_transfer
        staticInit_transferUnitTest)
target_link_libraries(fundUnitTest
        gtest_main
        staticInit_event
        staticInit_sington
        staticInit_commandBus
        staticInit_fund
        staticInit_fundUnitTest)
target_link_libraries(tansferFlowTest
        gtest_main
        staticInit_transfer
        staticInit_event
        staticInit_sington
        staticInit_commandBus
        staticInit_user
        staticInit_fund)
enable_testing()
add_test(NAME infrastructureTest COMMAND infrastructureTest)
add_test(NAME userUnitTest COMMAND userUnitTest)
add_test(NAME fundUnitTest COMMAND fundUnitTest)
add_test(NAME tansferUnitTest COMMAND tansferUnitTest)
add_test(NAME tansferFlowTest COMMAND tansferFlowTest)