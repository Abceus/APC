cmake_minimum_required(VERSION 3.4.1)

add_library(apc_jni SHARED
                main.cpp)

set(distribution_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../app/src/main/libs)
set_target_properties(apc_jni
                      PROPERTIES
                      LIBRARY_OUTPUT_DIRECTORY
                      "${distribution_DIR}/apc_jni/lib/${ANDROID_ABI}")
# add_custom_command(TARGET AndroidSo POST_BUILD
#                    COMMAND "${CMAKE_COMMAND}" -E
#                    copy "${CMAKE_CURRENT_SOURCE_DIR}/include/*"
#                    "${distribution_DIR}/AndroidSo/*"
#                    COMMENT "Copying AndroidSo to output directory")

target_include_directories(apc_jni PRIVATE include)
target_link_libraries(apc_jni
                        android
                        log 
                        APC
                        test_game
                        # EGL
                        # GLESv2
                        )