#
# cmake file
#

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)

set (PROJ_NAME lossFunctions)

PROJECT(${PROJ_NAME})

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES Clang)
  add_compile_options(-std=c++1y)
endif()

set (SRC src/HingeLoss.cpp
         src/LogLoss.cpp
         src/SquaredLoss.cpp)

set (INCLUDE include/HingeLoss.h
             include/LogLoss.h
             include/SquaredLoss.h)


source_group("src" FILES ${SRC})
source_group("include" FILES ${INCLUDE})

include_directories(include)
include_directories(../types/include)

add_library(${PROJ_NAME} ${SRC} ${INCLUDE})

set_property(TARGET ${PROJ_NAME} PROPERTY FOLDER "libraries")

#
# test project
#

set (TEST_NAME ${PROJ_NAME}_test)

include_directories(../testing/include)

add_executable(${TEST_NAME} test/test.cpp ${INCLUDE})

target_link_libraries(${TEST_NAME} lossFunctions testing)

set_property(TARGET ${TEST_NAME} PROPERTY FOLDER "tests")

add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})