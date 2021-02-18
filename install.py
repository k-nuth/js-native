# Copyright (c) 2016-2021 Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

import pip

def install(package):
    pip.main(['install', package])

if __name__ == '__main__':
    install('conan')
