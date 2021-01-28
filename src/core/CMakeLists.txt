cmake_minimum_required(VERSION 3.4.1)

project(APC)
set(CMAKE_CXX_STANDARD 20)

add_library(APC SHARED
        source/game.cpp
        source/transform.cpp
        source/clickable_area.cpp
        source/component.cpp
        source/scene_object.cpp
        source/color.cpp
        source/scene_manager.cpp
        source/context.cpp
        source/math_utils.cpp
        source/polygon.cpp
        source/vertex_batching.cpp
        source/texture.cpp
        source/scene_impl.cpp
        source/sprite.cpp)

target_include_directories(APC
        PRIVATE include/apc
        PUBLIC include)
