#!/usr/bin/python3
import sys

from build_system.module_manager import ModuleManager


def main():
    if len(sys.argv) < 3:
        print("Too few arguments")
        return

    mm = ModuleManager()
    mm.load_modules()
    mm.execute(*sys.argv[1:])

if __name__ == "__main__":
    main()