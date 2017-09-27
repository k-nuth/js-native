# python -c "exec(\"import shutil \nshutil.move('./build/deps/', '.') \")"
# python -c "exec(\"import os \ndir_path = os.path.dirname(os.path.realpath(__file__)) \nprint(dir_path) \")"
# python -c "exec(\"import os \nprint(os.getcwd()) \")"


# python -c "import os"

# import os
# cwd = os.getcwd()

# import os 
# dir_path = os.path.dirname(os.path.realpath(__file__))

import pip
import shutil
import os
from conans.client.conan_api import (Conan, default_manifest_folder)

def install(package):
    pip.main(['install', package])

def find(name, path):
    for root, dirs, files in os.walk(path):
        if name in files:
            return os.path.join(root, name)

def run_conan(reference, reference_fallback):
    c = Conan.factory()

    try:
        # c.remote_add(remote, url, verify_ssl, args.insert)
        c.remote_add('bitprim', 'https://api.bintray.com/conan/bitprim/bitprim')
    except:
        print ("Conan Remote exists, ignoring exception")


    try:
        # c.install(reference, verify=None, manifests=None)
        c.install(reference, verify=None, manifests_interactive=None, manifests=None)
        print('876128376128371263876128376128371263876128376128371263876128376128371263876128376128371263')
        pepe = find('nodecint.h', os.getcwd())
        print(pepe)
        print('876128376128371263876128376128371263876128376128371263876128376128371263876128376128371263')

    except:
        c.install(reference_fallback, verify=None, manifests_interactive=None, manifests=None)
        print('876128376128371263876128376128371263876128376128371263876128376128371263876128376128371263')
        pepe = find('nodecint.h', os.getcwd())
        print(pepe)
        shutil.move('./deps/', '..')
        pepe = find('nodecint.h', os.getcwd())
        print(pepe)
        print('876128376128371263876128376128371263876128376128371263876128376128371263876128376128371263')

if __name__ == '__main__':

    print('-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*')
    print(os.path.dirname(os.path.abspath(__file__)))
    print(os.getcwd())
    print('-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*')

    pepe = find('nodecint.h', os.getcwd())
    print(pepe)

    print('-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*')


    install('conan')
    run_conan('.', '..')

    # shutil.move('./deps/', '..')