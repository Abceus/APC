cmake_minimum_required(VERSION 3.4.1)

project(APC_glfw)
set(CMAKE_CXX_STANDARD 14)

add_executable(
        APC_glfw
        main.cpp
        )

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
target_include_directories(APC_glfw PRIVATE ${GLEW_INCLUDE_DIRS} include)
find_package(OpenGL REQUIRED)
target_link_libraries(APC_glfw APC test_game ${GLEW_LIBRARIES} glfw)