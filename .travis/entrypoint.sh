#!/bin/bash

# nvm install 8

echo "Fer 1"

# sudo apt-get install -y curl

echo "Fer 2"

# curl -sL http://deb.nodesource.com/setup_8.x | sudo -E bash -
wget -qO- http://deb.nodesource.com/setup_8.x | sudo -E bash -

# wget -O setup_8.x.sh http://deb.nodesource.com/setup_8.x 
# ls -ltra
# chmod +x setup_8.x.sh
# ./setup_8.x.sh


echo "Fer 3"

sudo apt-get install -y nodejs

echo "Fer 4"

# sudo apt-get install -y  nodejs
# sudo apt-get install -y  nodejs-legacy


echo "Fer 5"

sudo apt-get install -y  npm

echo "Fer 6"

sudo -H npm install npm@latest -g

echo "Fer 7"


sudo -H npm install -g node-gyp
sudo -H npm install -g node-pre-gyp
sudo -H npm install -g aws-sdk
sudo -H npm install -g node-pre-gyp-github

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
# node-pre-gyp configure build package
# node-pre-gyp-github publish
# node-pre-gyp-github publish --release

