from conans import ConanFile, CMake
# import os

class BitprimJs(ConanFile):
    name = "bitprim-js"
    version = "0.1"
    license = "http://www.boost.org/users/license.html"
    url = "https://github.com/bitprim/bitprim-js"
    description = "Bitcoin Full Node Library with Javascript interface"
    settings = "os", "compiler", "build_type", "arch"
    
    # options = {"shared": [True, False]}
    # default_options = "shared=False"

    generators = "cmake"
    # exports_sources = "src/*", "CMakeLists.txt", "cmake/*", "bitprim-node-cintConfig.cmake.in", "include/*", "test/*", "console/*"
    # package_files = "build/lbitprim-node-cint.so"
    # build_policy = "missing"

    # TODO(fernando): queda pendiente seleccionar el default Shared=False
    
    requires = (("bitprim-node-cint/0.3@bitprim/stable"))
    # requires = (("bitprim-node-cint/0.2@bitprim/stable"))

    # conan install bitprim-node-cint/0.3@bitprim/stable -o gmp:host=auto --build=gmp

    # default_options = "gmp:host=auto" #, "OpenSSL:shared=True"
    # build_policy = "gmp"

    # default_options = "bitprim-node-cint:shared=False" #, "OpenSSL:shared=True"

    # conan install bitprim-node-cint/0.2@bitprim/stable -o shared=True

    def imports(self):
        self.copy("*.h", "./deps/include/bitprim", "include/bitprim")
        self.copy("*.hpp", dst="./deps/include/bitprim", src="include/bitprim")
        self.copy("*.lib", dst="./deps/lib", src="lib")
        self.copy("*.a", dst="./deps/lib", src="lib")
        self.copy("*.dylib", dst="./deps/lib", src="lib")
        self.copy("*.so", dst="./deps/lib", src="lib")
        self.copy("*.dll", dst="./deps/lib", src="lib")


    # def build(self):
    # def package(self):
    # def package_info(self):
