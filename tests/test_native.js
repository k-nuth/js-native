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
// const bitprim = require('../lib/binding/Release/node-v48-linux-x64/bitprim-native')
const bitprim = require('../lib/binding/Release/node-v48-win32-x64/bitprim-native')


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
bitprim.executor_initchain(executor)
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

        // var version = bitprim.chain_header_get_version(header);
        // console.log(`chain_fetch_block_header_by_height, version: ${version}`)

        // var previous_block_hash = bitprim.chain_header_get_previous_block_hash(header);
        // // console.log(`chain_fetch_block_header_by_height, previous_block_hash: ${previous_block_hash}`)
        // var previous_block_hash_str = fromHash(previous_block_hash)
        // console.log(`chain_fetch_block_header_by_height, previous_block_hash_str: ${previous_block_hash_str}`)

        // var merkle = bitprim.chain_header_get_merkle(header);
        // // console.log(`chain_fetch_block_header_by_height, merkle: ${merkle}`)
        // var merkle_str = fromHash(merkle)
        // console.log(`chain_fetch_block_header_by_height, merkle_str: ${merkle_str}`)

        // var hash = bitprim.chain_header_get_hash(header);
        // // console.log(`chain_fetch_block_header_by_height, hash: ${hash}`)
        // var hash_str = fromHash(hash)
        // console.log(`chain_fetch_block_header_by_height, hash_str: ${hash_str}`)

        // var timestamp = bitprim.chain_header_get_timestamp(header);
        // console.log(`chain_fetch_block_header_by_height, timestamp: ${timestamp}`)

        // var timestamp_date = timestampToDate(timestamp)
        // console.log(`chain_fetch_block_header_by_height, timestamp_date: ${timestamp_date}`)


        // var bits = bitprim.chain_header_get_bits(header);
        // console.log(`chain_fetch_block_header_by_height, bits: ${bits}`)

        // var nonce = bitprim.chain_header_get_nonce(header);
        // console.log(`chain_fetch_block_header_by_height, nonce: ${nonce}`)

        


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


// bitprim.chain_fetch_block_by_height(chain, 2300, function (err, block, height) {
//     if (err == 0) {
//         console.log(`chain_fetch_block_by_height is OK, err:  ${err}, height: ${height}`)
//     } else {
//         console.log(`chain_fetch_block_by_height failed, err: ${err}, height: ${height}`)
//     }
// })


bitprim.chain_fetch_block_by_height(chain, 2300, function (err, block, height) {
    if (err == 0) {
        console.log(`chain_fetch_block_by_height is OK, err:  ${err}, height: ${height}`)

        var tx_count = bitprim.chain_block_transaction_count(block);
        console.log(`chain_fetch_block_by_height, tx_count: ${tx_count}`)

        var serialized_size = bitprim.chain_block_serialized_size(block, 0);
        console.log(`chain_fetch_block_by_height, serialized_size: ${serialized_size}`)

        var subsidy = bitprim.chain_block_subsidy(2300);
        console.log(`chain_fetch_block_by_height, subsidy: ${subsidy}`)

        var fees = bitprim.chain_block_fees(block);
        console.log(`chain_fetch_block_by_height, fees: ${fees}`)
        
        var claim = bitprim.chain_block_claim(block);
        console.log(`chain_fetch_block_by_height, claim: ${claim}`)
        
        
        var reward = bitprim.chain_block_reward(block, 2300);
        console.log(`chain_fetch_block_by_height, reward: ${reward}`)


        var merkle_root = fromHash(bitprim.chain_block_generate_merkle_root(block))
        console.log(`chain_fetch_block_by_height, merkle_root: ${merkle_root}`)

        var hash = fromHash(bitprim.chain_block_hash(block))
        console.log(`chain_fetch_block_by_height, hash: ${hash}`)

        var is_valid = bitprim.chain_block_is_valid(block);
        console.log(`chain_fetch_block_by_height, is_valid: ${is_valid}`)

        var tx_nth = bitprim.chain_block_transaction_nth(block, 0);
        // console.log(`chain_fetch_block_by_height, tx_nth: ${tx_nth}`)

        var sigops = bitprim.chain_block_signature_operations(block);
        console.log(`chain_fetch_block_by_height, sigops: ${sigops}`)

        var sigops2 = bitprim.chain_block_signature_operations_bip16_active(block, true);
        console.log(`chain_fetch_block_by_height, sigops2: ${sigops2}`)

        var total_inputs = bitprim.chain_block_total_inputs(block, true);
        console.log(`chain_fetch_block_by_height, total_inputs: ${total_inputs}`)

        var is_extra_coinbase = bitprim.chain_block_is_extra_coinbase(block);
        console.log(`chain_fetch_block_by_height, is_extra_coinbase: ${is_extra_coinbase}`)

        var is_final = bitprim.chain_block_is_final(block, 2300, 0);
        console.log(`chain_fetch_block_by_height, is_final: ${is_final}`)

        var is_distinct_transaction_set = bitprim.chain_block_is_distinct_transaction_set(block);
        console.log(`chain_fetch_block_by_height, is_distinct_transaction_set: ${is_distinct_transaction_set}`)

        var is_valid_coinbase_claim = bitprim.chain_block_is_valid_coinbase_claim(block, 2300);
        console.log(`chain_fetch_block_by_height, is_valid_coinbase_claim: ${is_valid_coinbase_claim}`)

        var is_valid_coinbase_script = bitprim.chain_block_is_valid_coinbase_script(block, 2300);
        console.log(`chain_fetch_block_by_height, is_valid_coinbase_script: ${is_valid_coinbase_script}`)

        var is_internal_double_spend = bitprim.chain_block_is_internal_double_spend(block);
        console.log(`chain_fetch_block_by_height, is_internal_double_spend: ${is_internal_double_spend}`)

        var is_valid_merkle_root = bitprim.chain_block_is_valid_merkle_root(block);
        console.log(`chain_fetch_block_by_height, is_valid_merkle_root: ${is_valid_merkle_root}`)
        



        var header = bitprim.chain_block_get_header(block);

        var version = bitprim.chain_header_get_version(header);
        console.log(`chain_fetch_block_by_height, version: ${version}`)
        
        var previous_block_hash = bitprim.chain_header_get_previous_block_hash(header);
        // console.log(`chain_fetch_block_by_height, previous_block_hash: ${previous_block_hash}`)
        var previous_block_hash_str = fromHash(previous_block_hash)
        console.log(`chain_fetch_block_by_height, previous_block_hash_str: ${previous_block_hash_str}`)
        
        var merkle = bitprim.chain_header_get_merkle(header);
        // console.log(`chain_fetch_block_by_height, merkle: ${merkle}`)
        var merkle_str = fromHash(merkle)
        console.log(`chain_fetch_block_by_height, merkle_str: ${merkle_str}`)
        
        var hash = bitprim.chain_header_get_hash(header);
        // console.log(`chain_fetch_block_by_height, hash: ${hash}`)
        var hash_str = fromHash(hash)
        console.log(`chain_fetch_block_by_height, hash_str: ${hash_str}`)
        
        var timestamp = bitprim.chain_header_get_timestamp(header);
        console.log(`chain_fetch_block_by_height, timestamp: ${timestamp}`)
        
        var timestamp_date = timestampToDate(timestamp)
        console.log(`chain_fetch_block_by_height, timestamp_date: ${timestamp_date}`)
        
        
        var bits = bitprim.chain_header_get_bits(header);
        console.log(`chain_fetch_block_by_height, bits: ${bits}`)
        
        var nonce = bitprim.chain_header_get_nonce(header);
        console.log(`chain_fetch_block_by_height, nonce: ${nonce}`)
        

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

        
        var version = bitprim.chain_transaction_version(tx)
        console.log(`chain_fetch_transaction, version: ${version}`)

        // bitprim.chain_transaction_set_version(tx)
        var hash = bitprim.chain_transaction_hash(tx)
        console.log(`chain_fetch_transaction, hash: ${hash}`)
        
        var hash_sighash_type = bitprim.chain_transaction_hash_sighash_type(tx, 0)
        console.log(`chain_fetch_transaction, hash_sighash_type: ${hash_sighash_type}`)

        var locktime = bitprim.chain_transaction_locktime(tx)
        console.log(`chain_fetch_transaction, locktime: ${locktime}`)

        var serialized_size = bitprim.chain_transaction_serialized_size(tx, true)
        console.log(`chain_fetch_transaction, serialized_size: ${serialized_size}`)

        var fees = bitprim.chain_transaction_fees(tx)
        console.log(`chain_fetch_transaction, fees: ${fees}`)

        var signature_operations = bitprim.chain_transaction_signature_operations(tx)
        console.log(`chain_fetch_transaction, signature_operations: ${signature_operations}`)

        var signature_operations_bip16_active = bitprim.chain_transaction_signature_operations_bip16_active(tx, true)
        console.log(`chain_fetch_transaction, signature_operations_bip16_active: ${signature_operations_bip16_active}`)

        var total_input_value = bitprim.chain_transaction_total_input_value(tx)
        console.log(`chain_fetch_transaction, total_input_value: ${total_input_value}`)

        var total_output_value = bitprim.chain_transaction_total_output_value(tx)
        console.log(`chain_fetch_transaction, total_output_value: ${total_output_value}`)

        var is_coinbase = bitprim.chain_transaction_is_coinbase(tx)
        console.log(`chain_fetch_transaction, is_coinbase: ${is_coinbase}`)

        var is_null_non_coinbase = bitprim.chain_transaction_is_null_non_coinbase(tx)
        console.log(`chain_fetch_transaction, is_null_non_coinbase: ${is_null_non_coinbase}`)

        var is_oversized_coinbase = bitprim.chain_transaction_is_oversized_coinbase(tx)
        console.log(`chain_fetch_transaction, is_oversized_coinbase: ${is_oversized_coinbase}`)

        var is_mature = bitprim.chain_transaction_is_mature(tx, 0)
        console.log(`chain_fetch_transaction, is_mature: ${is_mature}`)

        var is_overspent = bitprim.chain_transaction_is_overspent(tx)
        console.log(`chain_fetch_transaction, is_overspent: ${is_overspent}`)

        var is_double_spend = bitprim.chain_transaction_is_double_spend(tx, true)
        console.log(`chain_fetch_transaction, is_double_spend: ${is_double_spend}`)

        var is_missing_previous_outputs = bitprim.chain_transaction_is_missing_previous_outputs(tx)
        console.log(`chain_fetch_transaction, is_missing_previous_outputs: ${is_missing_previous_outputs}`)

        var is_final = bitprim.chain_transaction_is_final(tx)
        console.log(`chain_fetch_transaction, is_final: ${is_final}`)

        var is_locktime_conflict = bitprim.chain_transaction_is_locktime_conflict(tx)
        console.log(`chain_fetch_transaction, is_locktime_conflict: ${is_locktime_conflict}`)

        var outputs = bitprim.chain_transaction_outputs(tx)
        // console.log(`chain_fetch_transaction, outputs: ${outputs}`)

        var inputs = bitprim.chain_transaction_inputs(tx)
        // console.log(`chain_fetch_transaction, inputs: ${inputs}`)
        

        bitprim.chain_transaction_destruct(tx)
        

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