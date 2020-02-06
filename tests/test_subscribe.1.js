// test_native.js
// npm install kth-native --msvs_version=2015
// Para saber donde estan los comprimidos en el sitio de npm:
//      npm view kth-native dist.tarball
//         https://registry.npmjs.org/kth-native/-/kth-native-0.0.15.tgz


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



// ------------------------------------------------------------------------------------------------


function sleep(sleepDuration) {
    var now = new Date().getTime();
    while(new Date().getTime() < now + sleepDuration){ /* do nothing */ } 
}

// ------------------------------------------------------------------------------------------------

// const kth = require('../build/Release/kth')
// const kth = require('../lib/binding/Release/node-v48-win32-x64/kth-native')

// const kth = require('../lib/binding/Release/node-v57-win32-x64/kth-native')         // Windows Fernando
const kth = require('../lib/binding/Release/node-v48-linux-x64/kth-native')         // Linux Fernando


// const kth = require('kth-native')


function wait_until_block(chain, desired_height) {

    var height = 0

    kth.chain_fetch_last_height(chain, function (e, h) {
        if (e == 0) {
            // console.log(`chain_fetch_last_height is OK, err:  ${e}, height: ${h}`)
            height = h
        } else {
            // console.log(`chain_fetch_last_height failed, err: ${e}, height: ${h}`)
        }
    })

    // printf("wait_until_block; desired_height: %zd, error: %d, height: %zd\n", desired_height, error, height);
    // console.log(`chain_fetch_last_height is OK, err:  ${e}, height: ${h}`)


    while (height < desired_height) {
        kth.chain_fetch_last_height(chain, function (e, h) {
            if (e == 0) {
                // console.log(`chain_fetch_last_height is OK, err:  ${e}, height: ${h}`)
                height = h
            } else {
                // console.log(`chain_fetch_last_height failed, err: ${e}, height: ${h}`)
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








const executor = kth.executor_construct("", process.stdout, process.stderr);
// const executor = kth.executor_construct("", null, null)
kth.executor_initchain(executor)
kth.executor_run_wait(executor)

const chain = kth.executor_get_chain(executor)

kth.chain_subscribe_blockchain(executor, chain, function (e, fork_height, blocks_incoming, blocks_replaced) {
    if (e == 0) {
        console.log(`chain_subscribe_blockchain is OK, err:  ${e}, fork_height: ${fork_height}`)
    } else {
        console.log(`chain_subscribe_blockchain failed, err: ${e}, fork_height: ${fork_height}`)
    }

    return true
})


// wait_until_block(chain, 2300)
wait_until_block(chain, 230000)


var hash_arr = toHash('0000000091a5fdf4b5f5fe07ed869bf82049b3d61a403f2771b5cbd1937dad09')

//-----------------------------------


//-----------------------------------


console.log('... BEFORE EXIT ...')

kth.executor_destruct(executor)

