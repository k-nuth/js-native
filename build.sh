#  Windows: Se necesita Python 2.7 y MSVC
# -------------------------------

# Ubuntu
# -------------------------------
# sudo apt-get update
# sudo apt-get install nodejs
# sudo apt-get install nodejs-legacy
# sudo apt-get install npm
# npm install npm@latest -g

# node-gyp Installation
# -------------------------------
# sudo -H npm install -g node-gyp
# sudo -H npm install -g node-pre-gyp
# sudo -H npm install -g aws-sdk
# sudo -H npm install -g node-pre-gyp-github

# https://github.com/bchr02/node-pre-gyp-github


node-gyp configure
node-gyp build
node test.js

# --------------------------------------------------------------------------------

# rm -rf node_modules
npm cache clean
npm install
node-pre-gyp configure build package

export NODE_PRE_GYP_GITHUB_TOKEN=f45fa0b589039bb0b12214c85c5be69406516f38
set NODE_PRE_GYP_GITHUB_TOKEN=f45fa0b589039bb0b12214c85c5be69406516f38

node-pre-gyp-github publish

node-pre-gyp clean
node-gyp clean

npm install
npm publish


## node-pre-gyp package publish
## npm publish



# --------------------------------------------------------------------------------

# https://medium.com/@jdaudier/how-to-create-and-publish-your-first-node-js-module-444e7585b738
# https://github.com/arturadib/node-qt

# npm set init.author.name "Fernando Pelliccioni"
# npm set init.author.email "fpelliccioni@gmail.com"
# npm set init.author.url "http://bitprim.org"

# npm login

# npm init



# --------------------------------------------------------------------------------

npm view bitprim-native dist.tarball