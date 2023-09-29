cmake_minimum_required(VERSION 3.8)
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

project(${DIR_NAME} CXX)
set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
message(STATUS ${SOURCE_DIRS})
set(SOURCE_LIB ${SOURCE_DIRS})
add_compile_options(-Wall -Wextra -pedantic -Werror)

add_library(${PROJECT_NAME} SHARED ${SOURCE_LIB})
target_include_directories(${PROJECT_NAME} PUBLIC .)


find_package(GTest)
if (NOT GTest_FOUND)
    include(FetchContent)

    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG release-1.11.0
    )
    FetchContent_MakeAvailable(googletest)
endif ()
