// Copyright (c) 2016-2023 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

const binary = require('@mapbox/node-pre-gyp');
const path = require('path')
const kth_path = binary.find(path.resolve(path.join(__dirname,'./package.json')));
const kth = require(kth_path);

function print_settings(setts) {
    console.log(setts)
    console.log(setts.chain.cores);
    console.log(setts.chain.priority);
    console.log(setts.chain.byteFeeSatoshis);
    console.log(setts.chain.sigopFeeSatoshis);
    console.log(setts.chain.minimumOutputSatoshis);
    console.log(setts.chain.notifyLimitHours);
    console.log(setts.chain.reorganizationLimit);
    console.log(setts.chain.checkpoints.length);
    console.log(setts.chain.checkpoints[0].height);
    console.log(setts.chain.checkpoints[0].hash);
    console.log(setts.chain.fixCheckpoints);
    console.log(setts.chain.allowCollisions);
    console.log(setts.chain.easyBlocks);
    console.log(setts.chain.retarget);
    console.log(setts.chain.bip16);
    console.log(setts.chain.bip30);
    console.log(setts.chain.bip34);
    console.log(setts.chain.bip66);
    console.log(setts.chain.bip65);
    console.log(setts.chain.bip90);
    console.log(setts.chain.bip68);
    console.log(setts.chain.bip112);
    console.log(setts.chain.bip113);
    console.log(setts.chain.bchUahf);
    console.log(setts.chain.bchDaaCw144);
    console.log(setts.chain.bchPythagoras);
    console.log(setts.chain.bchEuclid);
    console.log(setts.chain.bchPisano);
    console.log(setts.chain.bchMersenne);
    console.log(setts.chain.bchFermat);
    console.log(setts.chain.bchEuler);
    console.log(setts.chain.bchGauss);
    console.log(setts.chain.bchDescartes);
    console.log(setts.chain.bchLobachevski);
    // console.log(setts.chain.bchGalois);

    console.log(setts.chain.galoisActivationTime);
    console.log(setts.chain.leibnizActivationTime);

    console.log(setts.chain.asertHalfLife);
    // ------------------------------------------------------------------------------------
    console.log(setts.database.directory);
    console.log(setts.database.dbMode);
    console.log(setts.database.reorgPoolLimit);
    console.log(setts.database.dbMaxSize);
    console.log(setts.database.safeMode);
    console.log(setts.database.cacheCapacity);
    // ------------------------------------------------------------------------------------
    console.log(setts.network.threads);
    console.log(setts.network.protocolMaximum);
    console.log(setts.network.protocolMinimum);
    console.log(setts.network.services);
    console.log(setts.network.invalidServices);
    console.log(setts.network.relayTransactions);
    console.log(setts.network.validateChecksum);
    console.log(setts.network.identifier);
    console.log(setts.network.inboundPort);
    console.log(setts.network.inboundConnections);
    console.log(setts.network.outboundConnections);
    console.log(setts.network.manualAttemptLimit);
    console.log(setts.network.connectBatchSize);
    console.log(setts.network.connectTimeoutSeconds);
    console.log(setts.network.channelHandshakeSeconds);
    console.log(setts.network.channelHeartbeatMinutes);
    console.log(setts.network.channelInactivityMinutes);
    console.log(setts.network.channelExpirationMinutes);
    console.log(setts.network.channelGerminationSeconds);
    console.log(setts.network.hostPoolCapacity);
    console.log(setts.network.hostsFile);
    console.log(setts.network.self.ip);
    console.log(setts.network.self.port);
    console.log(setts.network.blacklist.length);
    console.log(setts.network.peers.length);
    console.log(setts.network.seeds.length);
    console.log(setts.network.seeds[0].scheme);
    console.log(setts.network.seeds[0].host);
    console.log(setts.network.seeds[0].port);
    console.log(setts.network.debugFile);
    console.log(setts.network.errorFile);
    console.log(setts.network.archiveDirectory);
    console.log(setts.network.rotationSize);
    console.log(setts.network.minimumFreeSpace);
    console.log(setts.network.maximumArchiveSize);
    console.log(setts.network.maximumArchiveFiles);
    console.log(setts.network.statisticsServer.ip);
    console.log(setts.network.statisticsServer.port);
    console.log(setts.network.verbose);
    console.log(setts.network.useIpv6);
    console.log(setts.network.userAgentBlacklist.length);
    console.log(setts.network.userAgentBlacklist[0]);
    // ------------------------------------------------------------------------------------
    console.log(setts.node.syncPeers);
    console.log(setts.node.syncTimeoutSeconds);
    console.log(setts.node.blockLatencySeconds);
    console.log(setts.node.refreshTransactions);
    console.log(setts.node.compactBlocksHighBandwidth);

}

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

function test_encoding() {
    const addressStr = 'bitcoincash:qrcuqadqrzp2uztjl9wn5sthepkg22majyxw4gmv6p';

    const native = kth.wallet_payment_address_construct_from_string(addressStr);
    const valid = kth.wallet_payment_address_is_valid(native);
    console.log(`valid: ${valid}`);
    if ( ! valid) {
        kth.wallet_payment_address_destruct(native);
        return;
    }
    // const obj = fromNative(native);

    const encoded = kth.wallet_payment_address_encoded_cashaddr(native, false);
    // kth.wallet_payment_address_destruct(native);

    console.log(`addressStr: ${addressStr}`);
    console.log(`encoded:    ${encoded}`);




    // expect(result.ok).toBe(true);
    // const addr = result.obj;
    // expect(addr.encoded()).toBe('bitcoincash:qrcuqadqrzp2uztjl9wn5sthepkg22majyxw4gmv6p');
    // expect(addr.encodedCashAddr()).toBe('bitcoincash:qrcuqadqrzp2uztjl9wn5sthepkg22majyxw4gmv6p');
    // expect(addr.encodedLegacy()).toBe('1P3GQYtcWgZHrrJhUa4ctoQ3QoCU2F65nz');
}

function chain_fetch_last_height(chain) {
    return new Promise((resolve, reject) => {
        kth.chain_fetch_last_height(chain, function (e, h) {
            resolve({error: e, height: h});
            // if (e == 0) {
            //     resolve(h);
            // } else {
            //     reject(e);
            // }
        })
    });
}

async function wait_until_block(chain, desired_height) {

    var res = await chain_fetch_last_height(chain);
    console.log(`chain_fetch_last_height is OK, height: ${res.height}`)

    while (res.height < desired_height) {
        var res = await  chain_fetch_last_height(chain);
        console.log(`chain_fetch_last_height is OK, height: ${res.height}`)

        if (res.height < desired_height) {
            sleep(1000)
        }
    }
}

function toHex(array) {
    let str = "";
    for (let i = 0; i < array.length; ++i) {
        str += array[i].toString(16).padStart(2, '0');
    }
    return str;
}

function testBIP44Addresses() {
    const MAINNET_P2KH = 0x00;
    const MAINNET_P2SH = 0x05;
    const HD_FIRST_HARDENED_KEY = 0x80000000;   //(1 << 31)
    const HD_PRIVATE_MAINNET = 326702167824577054n;
    const HD_PRIVATE_TESTNET = 303293221666392015n;

    // car slab tail dirt wife custom front shield diet pear skull vapor gorilla token yard
    // https://iancoleman.io/bip39/
    // e0b6ebf43ebcaa428f59a1f9241019ba4c083a1c05d988677c8bf28ec6505ae07286515a9bb0bf98d836f582a94f29fc92bbe9a0a5805ce6dc4756a439ebd1d9

    const words = [
        'car', 'slab', 'tail', 'dirt', 'wife', 'custom', 'front',
        'shield', 'diet', 'pear', 'skull', 'vapor', 'gorilla', 'token', 'yard'
    ];


    let wl = kth.core_string_list_construct();
    console.log("------------------------------------------------");
    words.forEach(word => {
        // console.log(word);
        kth.core_string_list_push_back(wl, word);
    });
    console.log("------------------------------------------------");

    const seed = kth.wallet_mnemonics_to_seed(wl);
    // console.log("seed: ", seed);

    const m = kth.wallet_hd_private_construct_seed(seed, HD_PRIVATE_MAINNET);
    const m44h = kth.wallet_hd_private_derive_private(m, 44 + HD_FIRST_HARDENED_KEY);
    const m44h145h = kth.wallet_hd_private_derive_private(m44h, 145 + HD_FIRST_HARDENED_KEY);
    const m44h145h0h = kth.wallet_hd_private_derive_private(m44h145h, 0 + HD_FIRST_HARDENED_KEY);
    const m44h145h0h0 = kth.wallet_hd_private_derive_private(m44h145h0h, 0);

    console.log("BIP32 Root Key:                     ", kth.wallet_hd_private_encoded(m));
    console.log("BIP44 Account Extended Private Key: ", kth.wallet_hd_private_encoded(m44h145h0h));
    console.log("BIP44 Account Extended Public Key:  ", kth.wallet_hd_public_encoded(kth.wallet_hd_private_to_public(m44h145h0h)));
    console.log("BIP32 Account Extended Private Key: ", kth.wallet_hd_private_encoded(m44h145h0h0));
    console.log("BIP32 Account Extended Public Key:  ", kth.wallet_hd_public_encoded(kth.wallet_hd_private_to_public(m44h145h0h0)));

    // print addresses
    for (let i = 0; i < 20; ++i) {
        const key = kth.wallet_hd_private_derive_private(m44h145h0h0, i);
        const secret = kth.wallet_hd_private_secret(key);
        const ecpriv = kth.wallet_ec_private_construct_secret(secret, 0x8000, true);
        const point = kth.wallet_secret_to_public(secret);
        const ecpub = kth.wallet_ec_public_construct_from_point(point, true);
        const pa = kth.wallet_ec_public_to_payment_address(ecpub, MAINNET_P2KH);

        console.log(`Address       ${i}: ${kth.wallet_payment_address_encoded_cashaddr(pa, false)}`);
        console.log(`Token Address ${i}: ${kth.wallet_payment_address_encoded_cashaddr(pa, true)}`);
        console.log(`Public        ${i}: ${kth.wallet_ec_public_encoded(ecpub)}`);
        console.log(`Private       ${i}: ${kth.wallet_ec_private_encoded(ecpriv)}`);
    }
}

async function main() {
    // testBIP44Addresses();
    // return;
    // test_encoding();

    const mainnet = 0;
    const justChain = 1;
    const setts = kth.config_settings_default(mainnet);
    setts.database.dbMaxSize = 2 * 1024 * 1024;    // 2MiB
    // console.log(setts);
    print_settings(setts);
    // return;

    let started = false
    let error = 0;
    let node = kth.node_construct(setts, true);
    // kth.node_signal_stop(node);
    // kth.node_destruct(node);
    // return;

    console.log("before waiting for signal...");
    kth.node_init_run_and_wait_for_signal(node, justChain, function (err) {
        console.log("handler result: ", err);
        started = true;
        error = err;
    });
    console.log("after waiting for signal...");

    while (!started) {
        await sleep(1000);
    }
    if (error != 0) {
        console.log("error: ", error);
        kth.node_signal_stop(node);
        kth.node_destruct(node);
        return;
    }
    console.log("node started");

    // const res = await async_chain.fetch_block_by_height(this.native, height);
    // return [res[0], block.fromNative(res[1]), res[2]];

    const chain = kth.node_get_chain(node);
    // await wait_until_block(chain, 2300);

    // kth.chain_fetch_block_header_by_height(chain, 0, function (err, header, height) {
    //     if (err == 0) {
    //         console.log(`chain_fetch_block_header_by_height is OK, err:  ${err}, height: ${height}, header: ${header}`)
    //     } else {
    //         console.log(`chain_fetch_block_header_by_height failed, err: ${err}, height: ${height}`)
    //     }
    // })

    kth.chain_fetch_block_by_height(chain, 0, function (err, block, height) {
        if (err == 0) {
            console.log(`chain_fetch_block_by_height is OK, err:  ${err}, height: ${height}`)
            if (kth.chain_block_is_valid(block)) {
                console.log(`chain_block_is_valid is OK, err:  ${err}, height: ${height}`)
            } else {
                console.log(`chain_block_is_valid failed, err: ${err}, height: ${height}`)
            }

            const hash = kth.chain_block_hash(block);
            console.log(`chain_block_hash is OK, err:  ${err}, height: ${height}, hash: ${hash}`)
            console.log(block)


            const headerNative = kth.chain_block_header(block);
            console.log(headerNative);
            const version = kth.chain_header_version(headerNative);
            console.log(version);
            const prevHash = kth.chain_header_previous_block_hash(headerNative);
            console.log(prevHash);
            const merkle = kth.chain_header_merkle(headerNative);
            console.log(merkle);
            const timestamp = kth.chain_header_timestamp(headerNative);
            console.log(timestamp);
            const bits = kth.chain_header_bits(headerNative);
            console.log(bits);
            const nonce = kth.chain_header_nonce(headerNative);
            console.log(nonce);


        } else {
            console.log(`chain_fetch_block_by_height failed, err: ${err}, height: ${height}`)
        }
    })

    await sleep(5000);

    kth.node_signal_stop(node);
    kth.node_destruct(node);
}

// async function main() {
//     const mainnet = 0;
//     const setts = kth.config_settings_default(mainnet);
//     let node = kth.node_construct(setts, true);
//     kth.node_destruct(node);
// }

(async () => {
    try {
        // var text = await main();
        // console.log(text);
        await main();
    } catch (e) {
        console.log("error: ", e);
    }
})();
