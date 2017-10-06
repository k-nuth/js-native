import shutil
import os
from conans.client.conan_api import (Conan, default_manifest_folder)


def find(name, path):
    for root, dirs, files in os.walk(path):
        if name in files:
            return os.path.join(root, name)

def run_conan(reference, reference_fallback):
    c = Conan.factory()

    print(reference)
    print(reference_fallback)

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
        print('EXCEPTION --------------------------')

        c.install(reference_fallback, verify=None, manifests_interactive=None, manifests=None)
        print('876128376128371263876128376128371263876128376128371263876128376128371263876128376128371263')
        pepe = find('nodecint.h', os.getcwd())
        print(pepe)
        shutil.move('./deps/', '..')
        pepe = find('nodecint.h', os.getcwd())
        print(pepe)
        print('876128376128371263876128376128371263876128376128371263876128376128371263876128376128371263')

    print('run_conan - END')

if __name__ == '__main__':
    run_conan('.', '..')

    # shutil.move('./deps/', '..')