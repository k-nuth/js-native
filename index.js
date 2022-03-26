// Copyright (c) 2016-2022 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

const binary = require('@mapbox/node-pre-gyp');

const path = require('path')
const kth_path = binary.find(path.resolve(path.join(__dirname,'./package.json')));
// console.log(`kth_path: ${kth_path}`)
const kth = require(kth_path);
module.exports = kth;
