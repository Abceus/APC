#
# Copyright (C) 2016 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# Build one shared lib. When we build, we set the bin to $user/tmp, and
# remove it after build complete, so only the distribution place could be
# used for application linking.

cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_VERBOSE_MAKEFILE on)

add_library(AndroidSo SHARED
                source/base/context.cpp
                source/base/gl_renderer.cpp
                source/AndroidSo.cpp)

if(DEFINED GLES2)
        add_definitions(-DGLES2)
endif()

# copy out the lib binary and remove generated files
set(distribution_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../output)
set_target_properties(AndroidSo
                      PROPERTIES
                      LIBRARY_OUTPUT_DIRECTORY
                      "${distribution_DIR}/AndroidSo/lib/${ANDROID_ABI}")
add_custom_command(TARGET AndroidSo POST_BUILD
                   COMMAND "${CMAKE_COMMAND}" -E
                   copy "${CMAKE_CURRENT_SOURCE_DIR}/include/*"
                   "${distribution_DIR}/AndroidSo/*"
                   COMMENT "Copying AndroidSo to output directory")

target_include_directories(AndroidSo PRIVATE include)
target_link_libraries(AndroidSo
                        android
                        log 
                        EGL
                        GLESv2)