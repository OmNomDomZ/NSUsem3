cmake_minimum_required(VERSION 3.22)
get_filename_component(PROGRAM_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
message(STATUS "PROGRAM_NAME: ${PROGRAM_NAME}")

set( CMAKE_CXX_COMPILER "/pathto/g++" )
set( CMAKE_C_COMPILER "/pathto/gcc" )

project(${PROGRAM_NAME} CXX)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
message(STATUS ${SOURCE_DIRS})

message(STATUS "project name: ${PROJECT_NAME}")
add_executable(${PROGRAM_NAME} ${SOURCE_DIRS})
target_compile_options(${PROGRAM_NAME} PRIVATE -pedantic -Wall -Werror)
target_include_directories(${PROGRAM_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

