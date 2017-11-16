// test_native.js
// npm install bitprim-native --msvs_version=2015
// Para saber donde estan los comprimidos en el sitio de npm:
//      npm view bitprim-native dist.tarball
//         https://registry.npmjs.org/bitprim-native/-/bitprim-native-0.0.15.tgz


// ------------------------------------------------------------------------------------------------

var toType = function(obj) {
    return ({}).toString.call(obj).match(/\s([a-zA-Z]+)/)[1].toLowerCase()
}

// ------------------------------------------------------------------------------------------------

function timestampToDate(unix_timestamp) {
    // Create a new JavaScript Date object based on the timestamp
    // multiplied by 1000 so that the argument is in milliseconds, not seconds.
    var date = new Date(unix_timestamp*1000);
    // Hours part from the timestamp
    var hours = date.getHours();
    // Minutes part from the timestamp
    var minutes = "0" + date.getMinutes();
    // Seconds part from the timestamp
    var seconds = "0" + date.getSeconds();

    // Will display time in 10:30:23 format
    var formattedTime = hours + ':' + minutes.substr(-2) + ':' + seconds.substr(-2);

    return formattedTime
} 

function byteToHexString(uint8arr) {
    if (!uint8arr) {
        return '';
    }

    var hexStr = '';
    for (var i = 0; i < uint8arr.length; i++) {
        var hex = (uint8arr[i] & 0xff).toString(16);
        hex = (hex.length === 1) ? '0' + hex : hex;
        hexStr += hex;
    }

    return hexStr.toUpperCase();
}

function hexStringToByte(str) {
    if (!str) {
        return new Uint8Array();
    }

    var a = [];
    for (var i = 0, len = str.length; i < len; i+=2) {
        a.push(parseInt(str.substr(i,2),16));
    }

    return new Uint8Array(a);
}

function reverse(s) {
    return s.split("").reverse().join("");
}

function toHash(s) {
    return hexStringToByte(s).reverse();
}

function fromHash(arr) {
    return byteToHexString(arr.reverse());
}

// ------------------------------------------------------------------------------------------------
function sleep(sleepDuration) {
    var now = new Date().getTime();
    while(new Date().getTime() < now + sleepDuration){ /* do nothing */ } 
}
// ------------------------------------------------------------------------------------------------


var express = require('express')
, app = express()



// const bitprim = require('../build/Release/bitprim')
// const bitprim = require('../lib/binding/Release/node-v48-win32-x64/bitprim-native')
// const bitprim = require('../lib/binding/Release/node-v57-win32-x64/bitprim-native')         // Windows Fernando
const bitprim = require('../lib/binding/Release/node-v48-linux-x64/bitprim-native')         // Linux Fernando
// const bitprim = require('bitprim-native')



// const app = express()
const port = 8080

process.stdin.resume();//so the program will not close instantly

process.on("SIGINT", function () {
    console.log("captured SIGINT...");
    // bitprim.executor_destruct(executor)
    process.exit();
});

app.get('/', (request, response) => {
    response.send(`<!DOCTYPE html>
    <html>
     <head>
      <title>Server-sent events test</title>
      <style>html,body,#test{height:98%;}</style>
     </head>
     <body>
     </body>
    </html>`)
})

app.listen(port, (err) => {
    if (err) {
        return console.log('something bad happened', err)
    }

    console.log(`server is listening on ${port}`)
})






const executor = bitprim.executor_construct("", process.stdout, process.stderr);
// const executor = bitprim.executor_construct("", null, null)
bitprim.executor_initchain(executor)
bitprim.executor_run_wait(executor)

const chain = bitprim.executor_get_chain(executor)


function print_blocks(block_list) {
    var n = bitprim.chain_block_list_count(block_list)
    
    for (var i = 0; i < n; ++i) {
        var blk = bitprim.chain_block_list_nth(block_list, i)
        var blk_hash = bitprim.chain_block_hash(blk)
        console.log(`print_blocks, blk_hash: ${blk_hash}`)
    }    
}


bitprim.chain_subscribe_blockchain(executor, chain, function (e, fork_height, blocks_incoming, blocks_replaced) {
    if (e == 0) {
        // console.log(`chain_subscribe_blockchain is OK, err:  ${e}, fork_height: ${fork_height}, blocks_incoming: ${blocks_incoming}, blocks_replaced: ${blocks_replaced}`)
        // console.log(`chain_subscribe_blockchain is OK, err:  ${e}, fork_height: ${fork_height}`)

        if (fork_height % 100 == 0) {
            console.log(`chain_subscribe_blockchain is OK, err:  ${e}, fork_height: ${fork_height}`)
        }
    } else {
        // console.log(`chain_subscribe_blockchain failed, err: ${e}, fork_height: ${fork_height}, blocks_incoming: ${blocks_incoming}, blocks_replaced: ${blocks_replaced}`)
        console.log(`chain_subscribe_blockchain failed, err: ${e}, fork_height: ${fork_height}`)
    }

    if (blocks_incoming) {
        print_blocks(blocks_incoming)
        bitprim.chain_block_list_destruct(blocks_incoming)
    }

    if (blocks_replaced) {
        print_blocks(blocks_replaced)
        bitprim.chain_block_list_destruct(blocks_replaced)
    }

    return true
})

// setInterval(function() {
//     console.log('-*-*-*-*-*-*-*-*-*-* Subscribing to block notification -*-*-*-*-*-*-*-*-*-* ')

//     bitprim.chain_subscribe_blockchain(executor, chain, function (e, fork_height, blocks_incoming, blocks_replaced) {
//         if (e == 0) {
//             // console.log(`chain_subscribe_blockchain is OK, err:  ${e}, fork_height: ${fork_height}, blocks_incoming: ${blocks_incoming}, blocks_replaced: ${blocks_replaced}`)
//             // console.log(`chain_subscribe_blockchain is OK, err:  ${e}, fork_height: ${fork_height}`)
    
//             if (fork_height % 100 == 0) {
//                 console.log(`chain_subscribe_blockchain is OK, err:  ${e}, fork_height: ${fork_height}`)
//             }
//         } else {
//             // console.log(`chain_subscribe_blockchain failed, err: ${e}, fork_height: ${fork_height}, blocks_incoming: ${blocks_incoming}, blocks_replaced: ${blocks_replaced}`)
//             console.log(`chain_subscribe_blockchain failed, err: ${e}, fork_height: ${fork_height}`)
//         }
    
//         if (fork_height % 1000 == 0) {
//             console.log('-*-*-*-*-*-*-*-*-*-* Ending Block notification -*-*-*-*-*-*-*-*-*-* ')
//             return false;
//         }
    
//         if (blocks_incoming) {
//             var n = bitprim.chain_block_list_count(blocks_incoming)

//             for (var i = 0; i < n; ++i) {
//                 var blk = bitprim.chain_block_list_nth(blocks_incoming, i)
//                 var blk_hash = bitprim.chain_block_hash(blk)
//                 console.log(`chain_subscribe_blockchain failed, blk_hash: ${blk_hash}`)
//             }

//             bitprim.chain_block_list_destruct(blocks_incoming)
//         }

//         if (blocks_replaced) {
//             bitprim.chain_block_list_destruct(blocks_replaced)
//         }

//         return true
//     })

// }, 10000);






//-----------------------------------


//-----------------------------------


// console.log('... BEFORE EXIT ...')

// bitprim.executor_destruct(executor)

