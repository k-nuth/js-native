# Copyright (c) 2016-2022 Knuth Project developers.
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


capi_version = "0.36.0"

def install(package):
    print("Installing ")
    print(package)
    try:
        subprocess.check_call([sys.executable, "-m", "pip", "install", package])
    except subprocess.CalledProcessError as err:
        print("Failing trying to install the package ", err.returncode, err.output)

# def test_conan_install():
#     print("Testing Conan Installation ")
#     try:
#         subprocess.check_call([sys.executable, "-c", "import conans.client.conan_api; print(conans); conans.client.conan_api.Conan.factory()"])
#     except subprocess.CalledProcessError as err:
#         print("Failing testing Conan installation ", err.returncode, err.output)


def find(name, path):
    for root, dirs, files in os.walk(path):
        if name in files:
            return os.path.join(root, name)

# def replace_boost_lib_names_on_windows(path):
#     # print('replace_boost_lib_names_on_windows')
#     # print(platform)
#     if platform != "win32":
#         return

#     # print('replace_boost_lib_names_on_windows')

#     for root, dirs, files in os.walk(path):
#         # print(files)

#         for file in files:
#             newfile = re.sub(r"-\d_\d\d", "", file)
#             newfile = re.sub(r"-vc\d\d\d-mt", "", newfile)

#             # print(file)
#             # print(newfile)
#             if file != newfile:
#                 file = os.path.join(path, file)
#                 newfile = os.path.join(path, newfile)
#                 print(file)
#                 print(newfile)
#                 os.rename(file, newfile)

def exec_conan(args_param):
    print("Executing Conan ")

    args = [sys.executable, "-m", "conans.conan"]
    args.extend(args_param)
    print(args)

    try:
        # subprocess.check_call(args)
        # output = subprocess.check_output(args, stderr=subprocess.STDOUT, shell=True, timeout=3, universal_newlines=True)
        # subprocess.check_call(args, stderr=subprocess.STDOUT, shell=True, universal_newlines=True)
        subprocess.check_call(args, stderr=subprocess.STDOUT, universal_newlines=True)
        # print("----------------------------------------------------")
        # print("After subprocess.check_call")
        # print("----------------------------------------------------")
    except subprocess.CalledProcessError as err:
        print("Failing trying to execute Conan ", err.returncode, err.output)
    # else:
    #     print("Output: \n{}\n".format(output))

def accomodate_capi():
    extensions = ['.a', '.so', '.lib', '.dylib', '.dll']

    new_directory = './deps/lib/'
    starting_directory = './host/'

    # os.mkdir(new_directory)
    os.makedirs(new_directory, exist_ok=True)



    for root, dirs, files in os.walk(starting_directory):
        for file in files:
            if any(file.endswith(ext) for ext in extensions):
                file_path = os.path.join(root, file)
                shutil.move(file_path, new_directory)

    shutil.move(f'./host/c-api/{capi_version}/Release/x86_64/include', './deps/include')

def run_conan(reference, march_id, debug_build):
    # print('platform --------------------------')
    # print(platform)
    # print('platform --------------------------')

    exec_conan(['remote', 'add', 'kth', 'https://packages.kth.cash/api', '--force'])
    exec_conan(['config', 'install', 'https://github.com/k-nuth/ci-utils/raw/master/conan/config2023.zip'])

    install_args = ['install', reference, '--deploy=full_deploy']
    if march_id != None:
        install_args.extend(['-o', f'c-api/*:march_id={march_id}'])

    if debug_build:
        install_args.extend(['-s', 'build_type=Debug'])

    if platform == "win32":
        # self.options["c-api"].march_id = "ZLm9Pjh"
        # exec_conan(['install', reference, '-o', 'c-api/*:march_id={}'.format(march_id), '-s', 'compiler.runtime=MT'])
        install_args.extend(['-s', 'compiler.runtime=MT'])
        install_args.extend(['--build=missing'])
        exec_conan(install_args)
        capi_h = find('capi.h', os.getcwd())
        # print("----------------------------------------------------")
        # print(capi_h)
        # print("----------------------------------------------------")
        shutil.move('./host/', '..')
    elif platform == "linux":
        # install_args.extend(['-s', 'compiler.libcxx=libstdc++11'])
        install_args.extend(['--build=missing'])
        exec_conan(install_args)
    else:
        # exec_conan(['install', reference])
        # exec_conan(['install', reference, '-o', 'c-api/*:march_id={}'.format(march_id)])
        install_args.extend(['--build=missing'])
        exec_conan(install_args)

    accomodate_capi()

    capi_h = find('capi.h', os.getcwd())
    # print("----------------------------------------------------")
    # print(capi_h)
    # print("----------------------------------------------------")

    print('run_conan - END')
    # replace_boost_lib_names_on_windows('../host/c-api/lib')

def get_march(arch):
    march_id = os.getenv("KTH_MARCHID", "ZLm9Pjh")
    return march_id

    # arr = arch.split("-")
    # if len(arr) != 2:
    #     march_id = os.getenv("KTH_MARCHID", "ZLm9Pjh")
    #     # march_id = os.getenv("KTH_MARCHID", None)
    #     return march_id

    # march_id = arr[1]
    # return march_id

def get_debug_build():
    dbuild = os.getenv("KTH_DEBUG_BUILD", "0")
    return dbuild == "1"

if __name__ == '__main__':
    recipe_dir = sys.argv[1]
    # user_arch = sys.argv[2]
    user_arch = None
    march_id = get_march(user_arch)
    debug_build = get_debug_build()

    # print("----------------------------------------------------")
    # print("----------------------------------------------------")
    # print("----------------------------------------------------")
    # print("************** Conan Recipe directory: {}".format(recipe_dir))
    # print("************** User defined arch:      {}".format(user_arch))
    # print("************** Microarchitecture Id:   {}".format(march_id))
    # print("************** Debug Build:            {}".format(debug_build))

    # print("Python version")
    # print (sys.version)
    # print("Version info.")
    # print (sys.version_info)
    # print("Interpreter path.")
    # print(sys.executable)
    # print("----------------------------------------------------")
    # print("----------------------------------------------------")
    # print("----------------------------------------------------")

    install('conan')
    # test_conan_install()
    install('kthbuild')
    # test_conan_install()
    run_conan(recipe_dir, march_id, debug_build)
