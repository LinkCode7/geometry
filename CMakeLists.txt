cmake_minimum_required(VERSION 3.20)
project(geometry)

set(CMAKE_CXX_STANDARD 17)

# 设置输出路径，dll和exe必须在同一目录，否则运行时无法继续执行
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

file(GLOB SRC
       ${PROJECT_SOURCE_DIR}/*.cc
       ${PROJECT_SOURCE_DIR}/boolean2d/*.cc
       ${PROJECT_SOURCE_DIR}/geo2d/*.cc
       ${PROJECT_SOURCE_DIR}/sindy2d/*.cc
       ${PROJECT_SOURCE_DIR}/test/*.cc)

message(">>> SRC=${SRC}")

add_executable(${PROJECT_NAME} ${SRC})

#add_subdirectory(test)

# boost
set(Boost_INCLUDE_DIR "..//boost_1_79_0")
set(Boost_LIBRARY_DIRS "..//boost_1_79_0//lib")
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

# 动态链接googletest
include_directories("third_party/googletest/include")
set(GOOGLE_TEST_LIB_DIR "third_party/googletest/lib")
set(GOOGLE_TEST_DLLS "${CMAKE_SOURCE_DIR}/${GOOGLE_TEST_LIB_DIR}/gtest.dll")

find_library(GTEST gtest ${GOOGLE_TEST_LIB_DIR})
find_library(GTEST_MAIN gtest_main ${GOOGLE_TEST_LIB_DIR})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${GTEST} ${GTEST_MAIN})

if(NOT GTEST)
    message(FATAL_ERROR ">>> GTEST not found")
endif()
if(NOT GTEST_MAIN)
    message(FATAL_ERROR ">>> GTEST_MAIN not found")
endif()

# 拷贝dll
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${GOOGLE_TEST_DLLS} $<TARGET_FILE_DIR:${PROJECT_NAME}>)

