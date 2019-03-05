cmake_minimum_required(VERSION 3.4.1)

project(APC)
set(CMAKE_CXX_STANDARD 17)

if(DEFINED GLES2)
        add_definitions(-DGLES2)
endif()

add_library(APC SHARED
        source/base/context.cpp
        source/base/gl_renderer.cpp
        source/base/resource_manager.cpp
        source/base/resources/image.cpp
        source/base/resources/gl_texture.cpp)

target_include_directories(APC 
        PRIVATE ${OPENGL_INCLUDE_DIRS} 
        PUBLIC include)

if(DEFINED GLES2)
    target_link_libraries(APC EGL GLESv2)
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(APC ${OPENGL_LIBRARIES})
endif()