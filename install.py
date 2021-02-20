# Copyright (c) 2016-2021 Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

import pip
import shutil
import os
import re
import sys
from sys import platform
import importlib

def install(package):
    pip.main(['install', package])

def find(name, path):
    for root, dirs, files in os.walk(path):
        if name in files:
            return os.path.join(root, name)

def replace_boost_lib_names_on_windows(path):
    # print('replace_boost_lib_names_on_windows')
    # print(platform)
    if platform != "win32":
        return

    # print('replace_boost_lib_names_on_windows')

    for root, dirs, files in os.walk(path):
        # print(files)

        for file in files:
            newfile = re.sub(r"-\d_\d\d", "", file)
            newfile = re.sub(r"-vc\d\d\d-mt", "", newfile)

            # print(file)
            # print(newfile)
            if file != newfile:
                file = os.path.join(path, file)
                newfile = os.path.join(path, newfile)
                print(file)
                print(newfile)
                os.rename(file, newfile)

def get_conan():
    try:
        conan_api = importlib.import_module('conans.client.conan_api')
        return conan_api
    except ImportError:
        # print("Conan is not installed *****************************")
        return None

# def run_conan(reference, reference_fallback):
#     # New API in Conan 0.28
#     conan_api = get_conan()
#     if conan_api == None:
#         sys.exit('Conan is not installed')
#         return False

#     Conan = conan_api.Conan
#     c, _, _ = Conan.factory()

#     print(reference)
#     print(reference_fallback)

#     try:
#         # c.remote_add(remote, url, verify_ssl, args.insert)
#         c.remote_add('kth', 'https://api.bintray.com/conan/k-nuth/kth')
#     except:
#         print ("Conan Remote exists, ignoring exception.")

#     print('platform --------------------------')
#     print(platform)
#     print('platform --------------------------')


#     try:
#         win_setts = ["compiler.runtime=MT"]
#         if platform == "win32":
#             c.install(reference, verify=None, manifests_interactive=None, manifests=None, settings=win_setts)
#         else:
#             # c.install(reference, verify=None, manifests=None)
#             c.install(reference, verify=None, manifests_interactive=None, manifests=None)

#         pepe = find('capi.h', os.getcwd())
#         print(pepe)

#     except:
#         print('EXCEPTION --------------------------')
#         print('platform --------------------------')
#         print(platform)
#         print('platform --------------------------')

#         if platform == "win32":
#             c.install(reference_fallback, verify=None, manifests_interactive=None, manifests=None, settings=win_setts)
#         else:
#             c.install(reference_fallback, verify=None, manifests_interactive=None, manifests=None)

#         pepe = find('capi.h', os.getcwd())
#         print(pepe)
#         shutil.move('./deps/', '..')
#         pepe = find('capi.h', os.getcwd())
#         print(pepe)

#     print('run_conan - END')
#     replace_boost_lib_names_on_windows('../deps/lib')

def run_conan(reference):
    # New API in Conan 0.28
    conan_api = get_conan()
    if conan_api == None:
        sys.exit('Conan is not installed')
        return False

    Conan = conan_api.Conan
    c, _, _ = Conan.factory()

    print(reference)

    try:
        # c.remote_add(remote, url, verify_ssl, args.insert)
        c.remote_add('kth', 'https://api.bintray.com/conan/k-nuth/kth')
    except:
        print ("Conan Remote exists, ignoring exception.")

    print('platform --------------------------')
    print(platform)
    print('platform --------------------------')

    win_setts = ["compiler.runtime=MT"]
    if platform == "win32":
        c.install(reference, verify=None, manifests_interactive=None, manifests=None, settings=win_setts)
    else:
        c.install(reference, verify=None, manifests_interactive=None, manifests=None)

    pepe = find('capi.h', os.getcwd())
    print(pepe)

    # pepe = find('capi.h', os.getcwd())
    # print(pepe)
    # shutil.move('./deps/', '..')
    # pepe = find('capi.h', os.getcwd())
    # print(pepe)

    print('run_conan - END')
    replace_boost_lib_names_on_windows('../deps/lib')

if __name__ == '__main__':
    # print(sys.argv[1])
    install('conan')
    install('kthbuild')
    run_conan(sys.argv[1])
