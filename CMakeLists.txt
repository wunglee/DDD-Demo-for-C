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
# 添加头文件搜索路径
include_directories(/usr/local/include)
#添加库文件搜索路径
link_directories(/usr/local/lib)
# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)
add_library(staticInit_request src/framework_components/requestion_filters/static_init.cpp)
add_library(staticInit_event src/framework_components/domain_event/publish_subscribe_service.cpp
        src/framework_components/domain_event/memory_publish_subscribe_service.cpp)
add_library(staticInit_sington src/framework_components/naming_service/static_init.cpp)
add_executable(infrastructureTest test/unit_test/framework_test/framework_test.cpp)

add_library(staticInit_user src/bc/user/static_init.cpp)
add_library(staticInit_userUnitTest test/unit_test/bc/user/static_init.cpp)
add_executable(userUnitTest test/unit_test/bc/user/user_unit_test.cpp)

add_library(staticInit_fund src/bc/fund/static_init.cpp)
add_library(staticInit_fundUnitTest test/unit_test/bc/fund/static_init.cpp)
add_executable(fundUnitTest test/unit_test/bc/fund/fund_unit_test.cpp)

add_library(staticInit_transfer src/bc/transfer/static_init.cpp)
add_library(staticInit_transferUnitTest test/unit_test/bc/transfer/static_init.cpp)
add_executable(tansferUnitTest test/unit_test/bc/transfer/transfer_unit_test.cpp)

add_executable(tansferFlowTest test/integration_test/require_flow_test.cpp)

target_link_libraries(infrastructureTest
        gtest_main
        staticInit_event
        staticInit_sington
        staticInit_request
)
target_link_libraries(userUnitTest
        gtest_main
        staticInit_event
        staticInit_sington
        staticInit_request
        staticInit_user
        staticInit_userUnitTest)
target_link_libraries(tansferUnitTest
        gtest_main
        staticInit_event
        staticInit_sington
        staticInit_request
        staticInit_transfer
        staticInit_transferUnitTest)
target_link_libraries(fundUnitTest
        gtest_main
        staticInit_event
        staticInit_sington
        staticInit_request
        staticInit_fund
        staticInit_fundUnitTest)
target_link_libraries(tansferFlowTest
        gtest_main
        staticInit_transfer
        staticInit_event
        staticInit_sington
        staticInit_request
        staticInit_user
        staticInit_fund)
enable_testing()
add_test(NAME infrastructureTest COMMAND infrastructureTest)
add_test(NAME userUnitTest COMMAND userUnitTest)
add_test(NAME fundUnitTest COMMAND fundUnitTest)
add_test(NAME tansferUnitTest COMMAND tansferUnitTest)
add_test(NAME tansferFlowTest COMMAND tansferFlowTest)