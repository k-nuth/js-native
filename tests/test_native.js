// test_native.js
// npm install bitprim-native --msvs_version=2015
// Para saber donde estan los comprimidos en el sitio de npm:
//      npm view bitprim-native dist.tarball
//         https://registry.npmjs.org/bitprim-native/-/bitprim-native-0.0.15.tgz


function sleep( sleepDuration ){
    var now = new Date().getTime();
    while(new Date().getTime() < now + sleepDuration){ /* do nothing */ } 
}

// function wait_until_block(chain,desired_height) {

//     uint64_t height;
//     int error = chain_get_last_height(chain, &height);
//     printf("wait_until_block; desired_height: %zd, error: %d, height: %zd\n", desired_height, error, height);
    
//     while (error == 0 && height < desired_height) {
//         error = chain_get_last_height(chain, &height);
//         printf("wait_until_block; desired_height: %zd, error: %d, height: %zd\n", desired_height, error, height);
        
//         if (height < desired_height) {
//             printf("wait_until_block - 2\n");
//             // time.sleep(1)
//             std::this_thread::sleep_for(10s);
//             printf("wait_until_block - 3\n");
//         }
//     }

//     printf("wait_until_block - 4\n");
// }

const bitprim = require('../build/Release/bitprim')

const executor = bitprim.executor_construct("", process.stdout, process.stderr);
// const executor = bitprim.executor_construct("", null, null)
bitprim.executor_initchain(executor)
bitprim.executor_run_wait(executor)

const chain = bitprim.executor_get_chain(executor)

bitprim.chain_fetch_last_height(chain, function (err, height) {
    if (err == 0) {
        console.log(`chain_fetch_last_height is OK, err:  ${err}, height: ${height}`)
    } else {
        console.log(`chain_fetch_last_height failed, err: ${err}, height: ${height}`)
    }
})

var exit = false

var x = 0;
while (x < 10) {
    // console.log('.')
    sleep(1000);

    bitprim.chain_fetch_last_height(chain, function (err, height) {
        if (err == 0) {
            console.log(`chain_fetch_last_height is OK, err:  ${err}, height: ${height}`)
        } else {
            console.log(`chain_fetch_last_height failed, err: ${err}, height: ${height}`)
        }
    })
        
    ++x
}

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