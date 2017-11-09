#!/bin/bash

nvm install 8
npm install -g node-gyp
npm install -g node-pre-gyp
npm install -g aws-sdk
npm install -g node-pre-gyp-github

# sudo pip install --upgrade conan_package_tools
pip install --upgrade --user conan_package_tools
pip install conan --upgrade --user
conan user

conan remote add bitprim_temp https://api.bintray.com/conan/bitprim/bitprim

pwd

cd /home/conan/project

ls -ltra

conan install .

# npm cache clean
npm install
node-pre-gyp configure build package
node-pre-gyp-github publish
# node-pre-gyp-github publish --release

