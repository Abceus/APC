cmake_minimum_required(VERSION 3.4.1)

project(APC_OPENGL)
set(CMAKE_CXX_STANDARD 17)

if(DEFINED GLES2)
        add_definitions(-DGLES2)
endif()

add_library(APC_OPENGL SHARED
        source/gl_renderer.cpp
        source/resources/image.cpp
        source/resources/gl_texture.cpp)

target_include_directories(APC_OPENGL 
        PRIVATE ${OPENGL_INCLUDE_DIRS}
        PUBLIC include
        PRIVATE include/apc/opengl
        PRIVATE third)

if(DEFINED GLES2)
    target_link_libraries(APC_OPENGL GLESv3)
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(APC_OPENGL ${OPENGL_LIBRARIES})
endif()

add_subdirectory(third/glm)

target_link_libraries(APC_OPENGL APC glm)