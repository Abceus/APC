from build_system.module import Module
from build_system.utils import copy_changed_directory

import os
import subprocess
import shutil

class Android(Module):
    def configure(self):
        if not os.path.exists("./build/android"):
            os.mkdir("./build/android")
        copy_changed_directory("./android", "./build/android")
        copy_changed_directory("./src", "./build/android/lib/src/main/cpp/apc")
        copy_changed_directory("./test_game", "./build/android/lib/src/main/cpp/test_game")

    def build(self):
        copy_changed_directory("./test_game", "./build/android/lib/src/main/cpp/test_game")
        os.chdir("./build/android")
        subprocess.check_call("gradle build", stderr=subprocess.STDOUT, shell=True)

    def clean(self):
        shutil.rmtree('./build/android/')

    def run(self):
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

module_class = Android