cmake_minimum_required(VERSION 3.4.1)
set(CMAKE_CXX_STANDARD 14)

add_library(
        test_game SHARED
        source/test_game.cpp
        source/components/afro.cpp
        )
target_include_directories(test_game PUBLIC include)
target_link_libraries(test_game APC)