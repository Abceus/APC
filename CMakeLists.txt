cmake_minimum_required(VERSION 3.13)
project(androidPC)
set(CMAKE_CXX_STANDARD 14)

if(DEFINED GLES2)
        add_definitions(-DGLES2)
endif()

add_library(androidPC SHARED
        source/base/context.cpp
        source/base/gl_renderer.cpp)

add_executable(
        androidPC_exe
        main.cpp
        )

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
target_include_directories(androidPC_exe PRIVATE ${GLEW_INCLUDE_DIRS} include)
target_include_directories(androidPC PRIVATE ${OPENGL_INCLUDE_DIRS} include)
if(DEFINED GLES2)
        target_link_libraries(androidPC EGL GLESv2)
else()
        find_package(OpenGL REQUIRED)
        target_link_libraries(androidPC ${OPENGL_LIBRARIES})
endif()
target_link_libraries(androidPC_exe androidPC ${GLEW_LIBRARIES} glfw)