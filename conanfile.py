from conans import ConanFile, CMake


class PokemonConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = "tgbot/1.2", "boost/1.74.0"
    generators = "cmake"
    default_options = {}

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
