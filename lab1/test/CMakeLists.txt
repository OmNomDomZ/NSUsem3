# Устанавливаем минимальную версию CMake
cmake_minimum_required(VERSION 3.8)

# Устанавливаем имя проекта (это может быть любое имя)
project(my_tests CXX)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 20)

# Добавляем исполняемый файл для тестов
add_executable(my_tests FlatMap_test.cpp)

# Проверяем наличие GTest
find_package(GTest)
if (NOT GTest_FOUND)
    include(FetchContent)

    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG release-1.11.0
    )
    FetchContent_MakeAvailable(googletest)
endif()

# Линкуем исполняемый файл тестов с Google Test
target_link_libraries(my_tests
        gtest
        gtest_main
)
