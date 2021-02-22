# Copyright (c) 2016-2021 Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

# import pip
import shutil
import os
import re
import sys
from sys import platform
import importlib
import subprocess

# def install(package):
#     pip.main(['install', package])

# try:
#     import pandas as pd
# except ImportError:
#     subprocess.check_call([sys.executable, "-m", "pip", "install", 'pandas'])
# finally:
#     import pandas as pd


def install(package):
    print("----------------------------------------------------")
    print("----------------------------------------------------")
    print("----------------------------------------------------")
    print("Installing ")
    print(package)
    try:
        subprocess.check_call([sys.executable, "-m", "pip", "install", package])
    except subprocess.CalledProcessError as err:
        print("Failing trying to install the package, returncode: ")
        print(err.returncode)

def test_conan_install():
    print("----------------------------------------------------")
    print("----------------------------------------------------")
    print("----------------------------------------------------")
    print("Testing Conan Installation ")
    try:
        subprocess.check_call([sys.executable, "-c", "import conans.client.conan_api; print(conans); conans.client.conan_api.Conan.factory()"])
    except subprocess.CalledProcessError as err:
        print("Failing testing Conan installation, returncode: ")
        print(err.returncode)


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


def exec_conan(args_param):
    print("----------------------------------------------------")
    print("----------------------------------------------------")
    print("----------------------------------------------------")
    print("Executing Conan ")
    
    args = [sys.executable, "-m", "conans.conan"]
    args.extend(args_param)
    print(args)

    try:
        subprocess.check_call(args)
    except subprocess.CalledProcessError as err:
        print("Failing trying to execute Conan, returncode: ")
        print(err.returncode)

def run_conan(reference):
    print('platform --------------------------')
    print(platform)
    print('platform --------------------------')

    exec_conan(['remote', 'add', 'kth', 'https://api.bintray.com/conan/k-nuth/kth'])

    if platform == "win32":
        exec_conan(['install', reference, '-o', 'compiler.runtime=MT'])
        capi_h = find('capi.h', os.getcwd())
        print("----------------------------------------------------")
        print(capi_h)
        print("----------------------------------------------------")
        shutil.move('./deps/', '..')
    else:
        exec_conan(['install', reference])

    capi_h = find('capi.h', os.getcwd())
    print("----------------------------------------------------")
    print(capi_h)
    print("----------------------------------------------------")

    print('run_conan - END')
    replace_boost_lib_names_on_windows('../deps/lib')


# def get_conan():
#     try:
#         conan_api = importlib.import_module('conans.client.conan_api')
#         return conan_api
#     except ImportError:
#         # print("Conan is not installed *****************************")
#         return None

# def run_conan(reference):
#     # New API in Conan 0.28
#     conan_api = get_conan()
#     if conan_api == None:
#         sys.exit('Conan is not installed')
#         return False

#     Conan = conan_api.Conan
#     c, _, _ = Conan.factory()

#     print(reference)

#     try:
#         # c.remote_add(remote, url, verify_ssl, args.insert)
#         c.remote_add('kth', 'https://api.bintray.com/conan/k-nuth/kth')
#     except:
#         print ("Conan Remote exists, ignoring exception.")

#     print('platform --------------------------')
#     print(platform)
#     print('platform --------------------------')

#     win_setts = ["compiler.runtime=MT"]
#     if platform == "win32":
#         c.install(reference, verify=None, manifests_interactive=None, manifests=None, settings=win_setts)
#         capi_h = find('capi.h', os.getcwd())
#         print("----------------------------------------------------")
#         print(capi_h)
#         print("----------------------------------------------------")
#         shutil.move('./deps/', '..')
#     else:
#         c.install(reference, verify=None, manifests_interactive=None, manifests=None)

#     capi_h = find('capi.h', os.getcwd())
#     print("----------------------------------------------------")
#     print(capi_h)
#     print("----------------------------------------------------")

#     print('run_conan - END')
#     replace_boost_lib_names_on_windows('../deps/lib')

if __name__ == '__main__':
    print("----------------------------------------------------")
    print("----------------------------------------------------")
    print("----------------------------------------------------")
    print(sys.argv[1])
    print("Python version")
    print (sys.version)
    print("Version info.")
    print (sys.version_info)
    print("Interpreter path.")
    print(sys.executable)
    print("----------------------------------------------------")
    print("----------------------------------------------------")
    print("----------------------------------------------------")

    install('conan')
    test_conan_install()
    install('kthbuild')
    test_conan_install()
    run_conan(sys.argv[1])
