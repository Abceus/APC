cmake_minimum_required(VERSION 3.13)
project(andoirdPC)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(
        andoirdPC
        main.cpp
        source/base/context.cpp
        source/base/gl_renderer.cpp
        )


find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLEW_INCLUDE_DIRS})
target_link_libraries(andoirdPC ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} glfw)