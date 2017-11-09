#!/bin/bash

# nvm install 8

echo "Fer 1"

sudo apt-get install -y curl

echo "Fer 2"

curl -sL https://deb.nodesource.com/setup_8.x | sudo -E bash -
# wget -qO- https://deb.nodesource.com/setup_8.x | sudo -E bash -

# curl -sL https://deb.nodesource.com/setup_6.x | bash -
#   or
# wget -qO- https://deb.nodesource.com/setup_8.x | bash -
#

echo "Fer 3"

sudo apt-get install -y nodejs

echo "Fer 4"

# sudo apt-get install nodejs
# sudo apt-get install nodejs-legacy


echo "Fer 5"

sudo apt-get install npm

echo "Fer 6"

npm install npm@latest -g

echo "Fer 7"


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

