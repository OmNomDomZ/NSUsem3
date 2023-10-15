cmake_minimum_required(VERSION 3.5.1)
project(sound_processor CXX)

set(SRC main.cpp wav_loader.cpp wav_writer.cpp)

add_executable(${PROJECT_NAME} ${SRC})