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


// const bitprim = require(__dirname + '../build/Release/bitprim')


// var bitprim = null;

// // Load the precompiled binary for windows.
// if (process.platform == "win32" && process.arch == "x64") {
//     bitprim = require('./lib/binding/Release/node-v48-win32-x64/bitprim-native.node');

//     // bitprim = require('./bin/winx64/bitprim.node');
//     // bitprim = require(__dirname + './build/Release/bitprim.node')
//     // bitprim = require('./build/Release/bitprim.node')
// } else if (process.platform == "win32" && process.arch == "ia32") {
//     bitprim = require('./lib/binding/Release/node-v48-win32-x64/bitprim-native.node');
//     // bitprim = require('./bin/winx86/bitprim.node');  
//     // bitprim = require(__dirname + './build/Release/bitprim.node')
//     // bitprim = require('./build/Release/bitprim.node')
// } else {
// 	// Load the new built binary for other platforms.
//     bitprim = require('./build/Release/bitprim.node');  
//     // bitprim = require(__dirname + './build/Release/bitprim.node')
//     // bitprim = require('./build/Release/bitprim.node')
// }


var binary = require('node-pre-gyp');
var path = require('path')
var bitprim_path = binary.find(path.resolve(path.join(__dirname,'./package.json')));

console.log(`bitprim_path: ${bitprim_path}`)

var bitprim = require(bitprim_path);

// require('assert').equal(bitprim.hello(),"hello");

module.exports = bitprim;
