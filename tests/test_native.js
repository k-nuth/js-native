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

function reverse(s){
    return s.split("").reverse().join("");
}

function toHash(s) {
    return hexStringToByte(s).reverse();
}

function fromHash(arr) {
    return byteToHexString(arr.reverse());
}


// var hash_arr0 = toHash('0000000091a5fdf4b5f5fe07ed869bf82049b3d61a403f2771b5cbd1937dad09')
// var hash_arr1 = hexStringToByte('0000000091a5fdf4b5f5fe07ed869bf82049b3d61a403f2771b5cbd1937dad09')
// var hash_arr2 = new Uint8Array([21, 31, 21, 31, 21, 31, 21, 31, 21, 31, 21, 31, 21, 31, 21, 31, 21, 31, 21, 31, 21, 31, 21, 31, 21, 31, 21, 31, 21, 31, 21, 31])


// console.log(hash_arr0 instanceof Uint8Array)
// console.log(typeof hash_arr0)
// console.log(toType(hash_arr0))

// console.log(hash_arr1 instanceof Uint8Array)
// console.log(typeof hash_arr1)
// console.log(toType(hash_arr1))

// console.log(hash_arr2 instanceof Uint8Array)
// console.log(typeof hash_arr2)
// console.log(toType(hash_arr2))

// return
    

// ------------------------------------------------------------------------------------------------


function sleep(sleepDuration) {
    var now = new Date().getTime();
    while(new Date().getTime() < now + sleepDuration){ /* do nothing */ } 
}

// ------------------------------------------------------------------------------------------------

// const bitprim = require('../build/Release/bitprim')
const bitprim = require('../lib/binding/Release/node-v48-linux-x64/bitprim-native')


function wait_until_block(chain, desired_height) {

    var height = 0

    bitprim.chain_fetch_last_height(chain, function (e, h) {
        if (e == 0) {
            console.log(`chain_fetch_last_height is OK, err:  ${e}, height: ${h}`)
            height = h
        } else {
            console.log(`chain_fetch_last_height failed, err: ${e}, height: ${h}`)
        }
    })

    // printf("wait_until_block; desired_height: %zd, error: %d, height: %zd\n", desired_height, error, height);
    // console.log(`chain_fetch_last_height is OK, err:  ${e}, height: ${h}`)


    while (height < desired_height) {
        bitprim.chain_fetch_last_height(chain, function (e, h) {
            if (e == 0) {
                console.log(`chain_fetch_last_height is OK, err:  ${e}, height: ${h}`)
                height = h
            } else {
                console.log(`chain_fetch_last_height failed, err: ${e}, height: ${h}`)
            }
        })
    

        // printf("wait_until_block; desired_height: %zd, error: %d, height: %zd\n", desired_height, error, height);
        
        if (height < desired_height) {
            // printf("wait_until_block - 2\n");
            sleep(1000)
            // printf("wait_until_block - 3\n");
        }
    }

    // printf("wait_until_block - 4\n");
}








const executor = bitprim.executor_construct("", process.stdout, process.stderr);
// const executor = bitprim.executor_construct("", null, null)
// bitprim.executor_initchain(executor)
bitprim.executor_run_wait(executor)

const chain = bitprim.executor_get_chain(executor)

wait_until_block(chain, 2300)


var hash_arr = toHash('0000000091a5fdf4b5f5fe07ed869bf82049b3d61a403f2771b5cbd1937dad09')

//-----------------------------------



// bitprim.chain_fetch_block_height(chain, [21,31], function (err, height) { //ERROR!
// bitprim.chain_fetch_block_height(chain, new Uint8Array([21, 31]), function (err, height) { //ERROR!
bitprim.chain_fetch_block_height(chain, hash_arr, function (err, height) {
    if (err == 0) {
        console.log(`chain_fetch_block_height is OK, err:  ${err}, height: ${height}`)
    } else {
        console.log(`chain_fetch_block_height failed, err: ${err}, height: ${height}`)
    }
})


//-----------------------------------


// function arrayBufferToString(buffer){
//     var arr = new Uint8Array(buffer);
//     var str = String.fromCharCode.apply(String, arr);
//     if(/[\u0080-\uffff]/.test(str)){
//         throw new Error("this string seems to contain (still encoded) multibytes");
//     }
//     return str;
// }


bitprim.chain_fetch_block_header_by_height(chain, 2300, function (err, header, height) {
    if (err == 0) {
        console.log(`chain_fetch_block_header_by_height is OK, err:  ${err}, height: ${height}`)

        var version = bitprim.chain_header_get_version(header);
        console.log(`chain_fetch_block_header_by_height, version: ${version}`)

        var previous_block_hash = bitprim.chain_header_get_previous_block_hash(header);
        console.log(`chain_fetch_block_header_by_height, previous_block_hash: ${previous_block_hash}`)
        
        // var previous_block_hash_pepe = new Uint8Array(previous_block_hash)
        // console.log(`chain_fetch_block_header_by_height, previous_block_hash_pepe: ${previous_block_hash_pepe}`)

        var previous_block_hash_str = fromHash(previous_block_hash)
        console.log(`chain_fetch_block_header_by_height, previous_block_hash_str: ${previous_block_hash_str}`)

        var timestamp = bitprim.chain_header_get_timestamp(header);
        console.log(`chain_fetch_block_header_by_height, timestamp: ${timestamp}`)

        var timestamp_date = timestampToDate(timestamp)
        console.log(`chain_fetch_block_header_by_height, timestamp_date: ${timestamp_date}`)


        var bits = bitprim.chain_header_get_bits(header);
        console.log(`chain_fetch_block_header_by_height, bits: ${bits}`)

        var nonce = bitprim.chain_header_get_nonce(header);
        console.log(`chain_fetch_block_header_by_height, nonce: ${nonce}`)

        


        bitprim.chain_header_destruct(header);
    } else {
        console.log(`chain_fetch_block_header_by_height failed, err: ${err}, height: ${height}`)
    }
})


bitprim.chain_fetch_block_header_by_hash(chain, toHash('000000005845885b0f3e66a5a7377c408c7c42bad7528f44862f7b7e741bdb9e'), function (err, header, height) {
    if (err == 0) {
        console.log(`*********** chain_fetch_block_header_by_hash is OK, err:  ${err}, height: ${height}`)
    } else {
        console.log(`*********** chain_fetch_block_header_by_hash failed, err: ${err}, height: ${height}`)
    }
})



bitprim.chain_fetch_block_header_by_hash(chain, hash_arr, function (err, header, height) {
    if (err == 0) {
        console.log(`chain_fetch_block_header_by_hash is OK, err:  ${err}, height: ${height}`)
    } else {
        console.log(`chain_fetch_block_header_by_hash failed, err: ${err}, height: ${height}`)
    }
})

//-----------------------------------


bitprim.chain_fetch_block_by_height(chain, 2300, function (err, block, height) {
    if (err == 0) {
        console.log(`chain_fetch_block_by_height is OK, err:  ${err}, height: ${height}`)
    } else {
        console.log(`chain_fetch_block_by_height failed, err: ${err}, height: ${height}`)
    }
})

bitprim.chain_fetch_block_by_hash(chain, hash_arr, function (err, block, height) {
    if (err == 0) {
        console.log(`chain_fetch_block_by_hash is OK, err:  ${err}, height: ${height}`)
    } else {
        console.log(`chain_fetch_block_by_hash failed, err: ${err}, height: ${height}`)
    }
})

//-----------------------------------


bitprim.chain_fetch_merkle_block_by_height(chain, 2300, function (err, merkle_block, height) {
    if (err == 0) {
        console.log(`chain_fetch_merkle_block_by_height is OK, err:  ${err}, height: ${height}`)
    } else {
        console.log(`chain_fetch_merkle_block_by_height failed, err: ${err}, height: ${height}`)
    }
})

bitprim.chain_fetch_merkle_block_by_hash(chain, hash_arr, function (err, merkle_block, height) {
    if (err == 0) {
        console.log(`chain_fetch_merkle_block_by_hash is OK, err:  ${err}, height: ${height}`)
    } else {
        console.log(`chain_fetch_merkle_block_by_hash failed, err: ${err}, height: ${height}`)
    }
})


//-----------------------------------
// TODO(bitprim): implement compact blocks.
// bitprim.chain_fetch_compact_block_by_height(chain, 2300, function (err, compact_block, height) {
//     if (err == 0) {
//         console.log(`chain_fetch_compact_block_by_height is OK, err:  ${err}, height: ${height}`)
//     } else {
//         console.log(`chain_fetch_compact_block_by_height failed, err: ${err}, height: ${height}`)
//     }
// })

// bitprim.chain_fetch_compact_block_by_hash(chain, hash_arr, function (err, compact_block, height) {
//     if (err == 0) {
//         console.log(`chain_fetch_compact_block_by_hash is OK, err:  ${err}, height: ${height}`)
//     } else {
//         console.log(`chain_fetch_compact_block_by_hash failed, err: ${err}, height: ${height}`)
//     }
// })

//-----------------------------------
var tx_hash_arr = toHash('2c8e87226737f9a782e568bf744cf6757cd0f593184df80a61ab0e08c6d86733')

// bitprim.chain_fetch_transaction(chain, tx_hash_arr, false, function (err, tx, index, height) {
bitprim.chain_fetch_transaction(chain, tx_hash_arr, true, function (err, tx, index, height) {
    if (err == 0) {
        console.log(`chain_fetch_transaction is OK, err:  ${err}, index: ${index}, height: ${height}`)
    } else {
        console.log(`chain_fetch_transaction failed, err: ${err}, index: ${index}, height: ${height}`)
    }
})

// bitprim.chain_fetch_transaction_position(chain, tx_hash_arr, false, function (err, index, height) {
bitprim.chain_fetch_transaction_position(chain, tx_hash_arr, true, function (err, index, height) {
    if (err == 0) {
        console.log(`chain_fetch_transaction_position is OK, err:  ${err}, index: ${index}, height: ${height}`)
    } else {
        console.log(`chain_fetch_transaction_position failed, err: ${err}, index: ${index}, height: ${height}`)
    }
})
    
//-----------------------------------

//-----------------------------------


console.log('... BEFORE EXIT ...')

bitprim.executor_destruct(executor)





// function demo() {
//     console.log('Taking a break...');
//     sleep(2000);
//     console.log('Two second later');
// }

// demo();

// ------------------------------------------------------------

// function sleep(ms) {
//     return new Promise(resolve => setTimeout(resolve, ms));
// }

// async function demo() {
//     console.log('Taking a break...');
//     await sleep(2000);
//     console.log('Two second later');
// }
  
// demo();