# Copyright (c) 2016-2021 Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

from conans import ConanFile, CMake
# import os

class KnuthJsNative(ConanFile):
    name = "js"
    version = "0.1"
    license = "http://www.boost.org/users/license.html"
    url = "https://github.com/k-nuth/js-native"
    description = "Bitcoin full node as a Javascript library"
    settings = "os", "compiler", "build_type", "arch"

    # options = {"shared": [True, False]}
    # default_options = "shared=False"
    # TODO(fernando): use Shared=False as default

    generators = "cmake"
    requires = (("c-api/0.17.0@kth/stable"))

    def configure(self):
        ConanFile.configure(self)
        self.options["c-api"].db = "full"
        self.options["c-api"].march_id = "4fZKi37a595hP"

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
