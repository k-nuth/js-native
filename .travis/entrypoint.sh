#!/bin/bash

echo "KTH_GHA_MARCH_ID: ${KTH_GHA_MARCH_ID}"

node_setup="http://deb.nodesource.com/setup_$NODEJS_VERSION.x"
wget -qO- $node_setup | sudo -E bash -
sudo apt-get install -y nodejs
sudo -H npm install npm@latest -g

sudo -H npm install -g node-gyp
sudo -H npm install -g @mapbox/node-pre-gyp
# sudo -H npm install -g aws-sdk
sudo -H npm install -g node-pre-gyp-github

# # npm cache clean
# # pip install conan --upgrade --user
# pip install kthbuild --upgrade --user
# conan --version
# conan user



# npm set init.author.name "Fernando Pelliccioni"
# npm set init.author.email "fpelliccioni@gmail.com"
# npm set init.author.url "http://kth.cash"


# npm adduser <<!
# $NPM_USERNAME
# $NPM_PASSWORD
# $NPM_EMAIL
# !


cat ~/.npmrc
# echo _auth = $NPM_AUTH_TOKEN > ~/.npmrc
echo "//registry.npmjs.org/:_authToken=$NPM_AUTH_TOKEN" > ~/.npmrc
cat ~/.npmrc


# conan remote add kth_temp https://api.bintray.com/conan/k-nuth/kth

pwd

cd /home/conan/project

# ls -ltra

# conan install .

# npm cache clean
# npm install
# npm install --loglevel verbose
npm install --target_arch=${KTH_GHA_MARCH_ID} --loglevel verbose
npm run test

node-pre-gyp configure build package --target_arch=${KTH_GHA_MARCH_ID}
# node-pre-gyp-github publish  || true
node-pre-gyp-github publish --release  #|| true

node-pre-gyp clean
node-gyp clean

# npm install
npm install --target_arch=${KTH_GHA_MARCH_ID} --loglevel verbose

npm publish || true
