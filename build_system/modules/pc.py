from build_system.module import Module
from build_system.utils import copy_changed_directory

import os
import shutil
import subprocess

class PC(Module):
    def configure(self):
        if not os.path.exists("./build/pc/build"):
            os.makedirs("./build/pc/build")
        copy_changed_directory("./src", "./build/pc/apc")
        copy_changed_directory("./test_game", "./build/pc/test_game")
        copy_changed_directory("./glfw", "./build/pc/glfw")
        f = open("./build/pc/CMakeLists.txt","w+")
        f.write("cmake_minimum_required(VERSION 3.4.1)\n" +
                    "add_subdirectory(apc)\n" +
                    "add_subdirectory(test_game)\n" +
                    "add_subdirectory(glfw)")
        f.close()


    def build(self):
        copy_changed_directory("./test_game", "./build/pc/test_game")
        os.chdir("./build/pc/build")
        subprocess.check_call("cmake " + os.path.abspath(".."), stderr=subprocess.STDOUT, shell=True)
        subprocess.check_call("cmake --build " + os.path.abspath("."), stderr=subprocess.STDOUT, shell=True)

    def clean(self):
        shutil.rmtree('./build/pc/')

    def run(self):
        os.chdir("./build/pc/build/glfw")
        subprocess.check_call("./APC_glfw", stderr=subprocess.STDOUT, shell=True)

module_class = PC