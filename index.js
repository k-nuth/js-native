// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

var binary = require('node-pre-gyp');
var path = require('path')
var kth_path = binary.find(path.resolve(path.join(__dirname,'./package.json')));

console.log(`kth_path: ${kth_path}`)

var kth = require(kth_path);

// require('assert').equal(kth.hello(),"hello");

module.exports = kth;



//
// Load bindings binary
//
// var oldDir = process.cwd();
// try {
//   // ensure we're in the right location so we can dynamically load the bundled Qt libraries
//   process.chdir(__dirname + '/../deps/qt-4.8.0/' + process.platform + '/' + process.arch);
// } catch (e) {
//   // if no local deps/ dir, assume shared lib linking. keep going
// }
// var qt = require(__dirname + '/../build/Release/qt.node');


// process.chdir(oldDir);


// const kth = require(__dirname + '../build/Release/kth')


// var kth = null;

// // Load the precompiled binary for windows.
// if (process.platform == "win32" && process.arch == "x64") {
//     kth = require('./lib/binding/Release/node-v48-win32-x64/kth-bch-native.node');

//     // kth = require('./bin/winx64/kth.node');
//     // kth = require(__dirname + './build/Release/kth.node')
//     // kth = require('./build/Release/kth.node')
// } else if (process.platform == "win32" && process.arch == "ia32") {
//     kth = require('./lib/binding/Release/node-v48-win32-x64/kth-bch-native.node');
//     // kth = require('./bin/winx86/kth.node');  
//     // kth = require(__dirname + './build/Release/kth.node')
//     // kth = require('./build/Release/kth.node')
// } else {
// 	// Load the new built binary for other platforms.
//     kth = require('./build/Release/kth.node');  
//     // kth = require(__dirname + './build/Release/kth.node')
//     // kth = require('./build/Release/kth.node')
// }
