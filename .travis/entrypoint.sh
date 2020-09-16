#!/bin/bash

echo "Fer 0"


echo "Fer 1"

# sudo apt-get install -y curl

echo "Fer 2"

node_setup="http://deb.nodesource.com/setup_$NODEJS_VERSION.x"

# wget -qO- http://deb.nodesource.com/setup_8.x | sudo -E bash -
wget -qO- $node_setup | sudo -E bash -

echo "Fer 3"

sudo apt-get install -y nodejs

echo "Fer 4"

# sudo apt-get install -y  nodejs
# sudo apt-get install -y  nodejs-legacy


echo "Fer 5"

# sudo apt-get install -y  npm

echo "Fer 6"

sudo -H npm install npm@latest -g

echo "Fer 7"


sudo -H npm install -g node-gyp
sudo -H npm install -g node-pre-gyp
sudo -H npm install -g aws-sdk
sudo -H npm install -g node-pre-gyp-github

# npm cache clean



# sudo pip install --upgrade conan_package_tools
# pip install --upgrade --user conan_package_tools
# pip install conan --upgrade --user
pip install kthbuild --upgrade --user
conan user



echo "Fer 7A"

# npm set init.author.name "Fernando Pelliccioni"

# echo "Fer 7B"

# npm set init.author.email "fpelliccioni@gmail.com"

# echo "Fer 7C"

# npm set init.author.url "http://kth.cash"

# echo "Fer 7D"

# npm adduser <<!
# $NPM_USERNAME
# $NPM_PASSWORD
# $NPM_EMAIL
# !


cat ~/.npmrc
# echo _auth = $NPM_AUTH_TOKEN > ~/.npmrc
echo "//registry.npmjs.org/:_authToken=$NPM_AUTH_TOKEN" > ~/.npmrc
cat ~/.npmrc

echo "Fer 7E"


conan remote add kth_temp https://api.bintray.com/conan/k-nuth/kth

pwd

cd /home/conan/project

# ls -ltra

conan install .

# npm cache clean
npm install
node-pre-gyp configure build package
# node-pre-gyp-github publish  || true
node-pre-gyp-github publish --release  || true

node-pre-gyp clean
node-gyp clean

npm install

npm publish || true

