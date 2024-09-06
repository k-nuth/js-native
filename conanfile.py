# Copyright (c) 2016-2023 Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

from conan import ConanFile

class KnuthJsNative(ConanFile):
    name = "js"
    version = "0.1"
    license = "http://www.boost.org/users/license.html"
    url = "https://github.com/k-nuth/js-native"
    description = "Bitcoin full node as a Javascript library"
    settings = "os", "compiler", "build_type", "arch"

    requires = (("c-api/0.48.0"))

    def configure(self):
        self.options["c-api/*"].march_id = "ZLm9Pjh"
