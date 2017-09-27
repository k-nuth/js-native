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
# npm install -g node-gyp



node-gyp configure
node-gyp build
node test.js

----------------------------------------

# rm -rf node_modules
npm cache clean
npm install
node-pre-gyp configure
node-pre-gyp build package
npm publish



----------------------------------------

# https://medium.com/@jdaudier/how-to-create-and-publish-your-first-node-js-module-444e7585b738
# https://github.com/arturadib/node-qt

# npm set init.author.name "Fernando Pelliccioni"
# npm set init.author.email "fpelliccioni@gmail.com"
# npm set init.author.url "http://bitprim.org"

# npm login

# npm init
