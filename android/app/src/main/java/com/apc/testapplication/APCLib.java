/*
 * Copyright (C) 2007 The Android Open Source Project
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
 */

package com.apc.testapplication;
import android.content.res.AssetManager;

// Wrapper for native library

public class APCLib {

     static {
         System.loadLibrary("apc_jni");
     }

     public static native void init(AssetManager assetManager);
     public static native void screenSizeChanged(int width, int height);
     public static native void draw();
     public static native void update( float dt );
     public static native void button( int x, int y );
     public static native void altButton( int x, int y );
     public static native void holdedMove( int x, int y );
     public static native void drag( int x, int y );
     public static native void drop( int x, int y );
     public static native void zoom( float delta );
}
