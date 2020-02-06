import shutil
import os
import re
# import platform
from sys import platform

from conans.client.conan_api import (Conan, default_manifest_folder)


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
                # print(file)
                # print(newfile)
                os.rename(file, newfile)


def run_conan(reference, reference_fallback):
    # New API in Conan 0.28
    c, _, _ = Conan.factory()

    print(reference)
    print(reference_fallback)

    try:
        # c.remote_add(remote, url, verify_ssl, args.insert)
        c.remote_add('kth', 'https://api.bintray.com/conan/k-nuth/kth')
    except:
        print ("Conan Remote exists, ignoring exception")

    try:
        # c.install(reference, verify=None, manifests=None)
        c.install(reference, verify=None, manifests_interactive=None, manifests=None)
        print('11 876128376128371263876128376128371263876128376128371263876128376128371263876128376128371263')
        pepe = find('nodecint.h', os.getcwd())
        print(pepe)
        print('11 876128376128371263876128376128371263876128376128371263876128376128371263876128376128371263')

    except:
        print('EXCEPTION --------------------------')

        c.install(reference_fallback, verify=None, manifests_interactive=None, manifests=None)
        print('22 876128376128371263876128376128371263876128376128371263876128376128371263876128376128371263')
        pepe = find('nodecint.h', os.getcwd())
        print(pepe)
        shutil.move('./deps/', '..')
        pepe = find('nodecint.h', os.getcwd())
        print(pepe)
        print('22 876128376128371263876128376128371263876128376128371263876128376128371263876128376128371263')

    print('run_conan - END')
    replace_boost_lib_names_on_windows('../deps/lib')

# line = 'libboost_system-vc140-mt-1_64.lib'

# # line = re.sub(r"</?\[\d+>", "", line)

# # libboost_\w+-vc\d\d\d-mt-\d_\d\d
# line = re.sub(r"-\d_\d\d", "", line)
# line = re.sub(r"-vc\d\d\d-mt", "", line)

# print(line)


if __name__ == '__main__':
    run_conan('.', '..')

    # shutil.move('./deps/', '..')