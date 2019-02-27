/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <cstring>
#include <jni.h>
#include <cinttypes>
#include <android/log.h>
#include <string>
#include "core/game.h"
#include "base/context.h"
#include "base/gl_renderer.h"
#include "test_game.h"

#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, "hello-libs::", __VA_ARGS__))

/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   app/src/main/java/com/example/hellolibs/MainActivity.java
 */

const int WIDTH = 800, HEIGHT = 600;

extern "C" JNIEXPORT void JNICALL
Java_com_apc_testapplication_APCLib_init(JNIEnv *env, jobject thiz) {
  APC::Context::getInstance().init<APC::GLRenderer, TestGame>(WIDTH, HEIGHT);
  APC::Context::getInstance().setLogFunction( [&](std::stringstream& ss){ LOGI( "%s", ss.str().c_str() ); });
}

extern "C" JNIEXPORT void JNICALL
Java_com_apc_testapplication_APCLib_draw(JNIEnv *env, jobject thiz) {
APC::Context::getInstance().draw();
}

extern "C" JNIEXPORT void JNICALL
Java_com_apc_testapplication_APCLib_update(JNIEnv *env, jobject thiz, jfloat dt) {
APC::Context::getInstance().update( static_cast<float>( dt ) );
}

extern "C" JNIEXPORT void JNICALL
Java_com_apc_testapplication_APCLib_button(JNIEnv *env, jobject thiz, jint x, jint y) {
APC::Context::getInstance().button( { static_cast<int>( x ), static_cast<int>( y ) } );
}

extern "C" JNIEXPORT void JNICALL
Java_com_apc_testapplication_APCLib_altButton(JNIEnv *env, jobject thiz, jint x, jint y) {
APC::Context::getInstance().altButton( { static_cast<int>( x ), static_cast<int>( y ) } );
}

extern "C" JNIEXPORT void JNICALL
Java_com_apc_testapplication_APCLib_holdedMove(JNIEnv *env, jobject thiz, jint x, jint y) {
APC::Context::getInstance().holdedMove( { static_cast<int>( x ), static_cast<int>( y ) } );
}

extern "C" JNIEXPORT void JNICALL
Java_com_apc_testapplication_APCLib_drag(JNIEnv *env, jobject thiz, jint x, jint y) {
APC::Context::getInstance().drag( { static_cast<int>( x ), static_cast<int>( y ) } );
}

extern "C" JNIEXPORT void JNICALL
Java_com_apc_testapplication_APCLib_drop(JNIEnv *env, jobject thiz, jint x, jint y) {
APC::Context::getInstance().drop( { static_cast<int>( x ), static_cast<int>( y ) } );
}

extern "C" JNIEXPORT void JNICALL
Java_com_apc_testapplication_APCLib_zoom(JNIEnv *env, jobject thiz, jfloat delta) {
APC::Context::getInstance().zoom( static_cast<float>( delta ) );
}
