import os
import pkgutil
import imp


class ModuleManager:
    def __init__(self):
        self.modules = {}

    def load_modules(self):
        path = os.path.join(os.path.dirname(__file__), "modules")
        for loader, name, ispkg in pkgutil.iter_modules([path]):
            file, pathname, desc = imp.find_module(name, [path])
            module_name = "build_system.modules.{0}".format(name)

            try:
                module = imp.load_module(name, file, pathname, desc)

                if hasattr(module, "module_class"):
                    module = getattr(module, "module_class")
                    self.modules[name] = module()

                if file:
                    file.close()
            except Exception as e:
                print("Failed to load module {0}:\n".format(name))
                print(e)

                continue

    def execute(self, module_name, command, *args):
        module = self.modules[module_name]
        if module:
            if command == "configure":
                module.configure()
            elif command == "build":
                module.build(*args)
            elif command == "run":
                module.run(*args)
            elif command == "clean":
                module.clean(*args)
    