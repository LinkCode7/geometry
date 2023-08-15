cmake_minimum_required(VERSION 3.20)
project(test)

set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

file(GLOB SRC_TEST
       ${PROJECT_SOURCE_DIR}/*.cc
       ${PROJECT_SOURCE_DIR}/sindy2d/*.cc)

add_executable(${PROJECT_NAME} ${SRC_TEST})

target_link_libraries(${PROJECT_NAME} gtest gtest_main)

include_directories("third_party/googletest/include")
set(GOOGLE_TEST_LIB_DIR "third_party/googletest/lib")
set(GOOGLE_TEST_DLLS "${CMAKE_SOURCE_DIR}/${GOOGLE_TEST_LIB_DIR}/gtest.dll")

# 动态链接googletest
find_library(GTEST gtest ${GOOGLE_TEST_LIB_DIR})
find_library(GTEST_MAIN gtest_main ${GOOGLE_TEST_LIB_DIR})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${GTEST} ${GTEST_MAIN})
