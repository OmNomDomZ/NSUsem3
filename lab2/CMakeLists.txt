cmake_minimum_required(VERSION 3.5.1)
project(sound_processor CXX)

set(SRC main.cpp wav.cpp exceptions.cpp parser.cpp)

add_executable(${PROJECT_NAME} ${SRC})