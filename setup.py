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
from conans.client.conan_api import (Conan, default_manifest_folder)

def install(package):
    pip.main(['install', package])

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
    except:
        c.install(reference_fallback, verify=None, manifests_interactive=None, manifests=None)
        shutil.move('./deps/', '..')

if __name__ == '__main__':
    install('conan')
    run_conan('.', '..')

    # shutil.move('./deps/', '..')