from abc import ABCMeta, abstractmethod

class Module(metaclass=ABCMeta):
    @abstractmethod
    def configure(self, *args):
        pass

    @abstractmethod
    def build(self, *args):
        pass

    @abstractmethod
    def clean(self, *args):
        pass

    @abstractmethod
    def run(self, *args):
        pass