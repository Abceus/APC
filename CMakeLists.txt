cmake_minimum_required(VERSION 3.13)
project(andoirdPC)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(andoirdPC
        main.cpp
        source/base/context.cpp
        source/base/gl_renderer.cpp
        source/base/game.cpp)