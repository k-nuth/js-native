from conans import ConanFile, CMake
# import os

class KnuthJs(ConanFile):
    name = "js"
    version = "0.1"
    license = "http://www.boost.org/users/license.html"
    url = "https://github.com/k-nuth/js-native"
    description = "Bitcoin Full Node Library with Javascript interface"
    settings = "os", "compiler", "build_type", "arch"
    
    # options = {"shared": [True, False]}
    # default_options = "shared=False"

    generators = "cmake"
    # exports_sources = "src/*", "CMakeLists.txt", "cmake/*", "kth-Config.cmake.in", "include/*", "test/*", "console/*"
    # package_files = "build/lkth-c-api.so"
    # build_policy = "missing"

    # TODO(fernando): use Shared=False as default
    
    requires = (("c-api/0.1.0@kth/stable"))

    # conan install c-api/0.8@kth/stable -o gmp:host=auto --build=gmp

    # default_options = "gmp:host=auto" #, "OpenSSL:shared=True"
    # build_policy = "gmp"

    # default_options = "c-api:shared=False" #, "OpenSSL:shared=True"

    # conan install c-api/0.2@kth/stable -o shared=True

    def imports(self):
        self.copy("*.h", "./deps/include/kth", "include/kth")
        self.copy("*.hpp", dst="./deps/include/kth", src="include/kth")
        self.copy("*.lib", dst="./deps/lib", src="lib")
        self.copy("*.a", dst="./deps/lib", src="lib")
        self.copy("*.dylib", dst="./deps/lib", src="lib")
        self.copy("*.so", dst="./deps/lib", src="lib")
        self.copy("*.dll", dst="./deps/lib", src="lib")


    # def build(self):
    # def package(self):
    # def package_info(self):
