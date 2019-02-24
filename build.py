#!/usr/bin/python
import os
import shutil
import subprocess
import sys

def android_build():
    if not os.path.exists("./build"):
        os.mkdir("./build")
    if not os.path.exists("./build/android"):
        shutil.copytree("./android", "./build/android")
        shutil.copytree("./test_game", "./build/android/lib/src/main/cpp/test_game")
        shutil.copytree("./src", "./build/android/lib/src/main/cpp/apc")
    os.chdir("./build/android")
    subprocess.check_call("gradle build", stderr=subprocess.STDOUT, shell=True)

def android_run():
    # TODO: 
    # 1) Check running devices
    # 2) Select from running device, update or run emulator
    # 3) Wait device
    # 4) Install apk
    # 5) Run application
    adb = os.path.join(os.environ['ANDROID_HOME'], "platform-tools", "adb")
    subprocess.check_call( adb + " wait-for-device", stderr=subprocess.STDOUT, shell=True)
    subprocess.check_call( adb + " install ./build/android/app/build/outputs/apk/debug/app-debug.apk", stderr=subprocess.STDOUT, shell=True)
    subprocess.check_call( adb + " shell am start -a android.intent.action.MAIN -n com.apc.testapplication/.MainActivity", stderr=subprocess.STDOUT, shell=True)

def android_clean():
    shutil.rmtree('./build/android/')

def pc_build():
    if not os.path.exists("./build"):
        os.mkdir("./build")
    if not os.path.exists("./build/pc"):
        os.mkdir("./build/pc")
        os.mkdir("./build/pc/build")
        shutil.copytree("./src", "./build/pc/apc")
        shutil.copytree("./test_game", "./build/pc/test_game")
        shutil.copytree("./glfw", "./build/pc/glfw")
        f = open("./build/pc/CMakeLists.txt","w+")
        f.write("cmake_minimum_required(VERSION 3.4.1)\n" +
                    "add_subdirectory(apc)\n" +
                    "add_subdirectory(test_game)\n" +
                    "add_subdirectory(glfw)")
        f.close()
    os.chdir("./build/pc/build")
    subprocess.check_call("cmake " + os.path.abspath(".."), stderr=subprocess.STDOUT, shell=True)
    subprocess.check_call("make", stderr=subprocess.STDOUT, shell=True)

def pc_run():
    os.chdir("./build/pc/build/glfw")
    subprocess.check_call("./APC_glfw", stderr=subprocess.STDOUT, shell=True)

def pc_clean():
    shutil.rmtree('./build/pc/')

def main():
    if len(sys.argv) < 3:
        print("Too few arguments")
        return
    android = sys.argv[1] == "android"
    pc = sys.argv[1] == "pc"
    build = sys.argv[2] == "build"
    run = sys.argv[2] == "run"
    clean = sys.argv[2] == "clean"

    if android:
        if build:
            android_build()
        elif run:
            android_run()
        elif clean:
            android_clean()
    elif pc:
        if build:
            pc_build()
        elif run:
            pc_run()
        elif clean:
            pc_clean()


if __name__ == "__main__":
    main()