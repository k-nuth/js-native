// Copyright (c) 2016-2021 Knuth Project developers.
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
    console.log(setts.chain.gaussActivationTime);
    console.log(setts.chain.asertHalfLife);
    // ------------------------------------------------------------------------------------
    console.log(setts.database.directory);
    console.log(setts.database.flushWrites);
    console.log(setts.database.fileGrowthRate);
    console.log(setts.database.indexStartHeight);
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

// async function main() {

//     const mainnet = 0;
//     const setts = kth.config_settings_default(mainnet);
    
//     let node = kth.node_construct(setts, true);
    
//     // var node = kth.node_construct("/home/fernando/testnet4/testnet4.cfg", process.stdout, process.stderr);
//     // var node = kth.node_construct("/home/fernando/testnet4/testnet4.cfg", null, null);
//     // const node = kth.node_construct("", null, null)
//     // kth.node_initchain(node)
//     // kth.node_run_wait(node)

//     kth.node_init_run_and_wait_for_signal(node, function (err) {
//         console.log(err);
//     });

//     setTimeout(function() {
//         console.log('program exit...');
//         kth.node_signal_stop(node);
//         kth.node_destruct(node);
//     }, 15000);


// }

async function main() {

    const mainnet = 0;
    const justChain = 1;
    const setts = kth.config_settings_default(mainnet);
    
    let node = kth.node_construct(setts, true);
    
    kth.node_init_run_and_wait_for_signal(node, justChain, function (err) {
        console.log("handler result: ");
        console.log(err);
    });

    setTimeout(function() {
        console.log('program exit...');
        kth.node_signal_stop(node);
        kth.node_destruct(node);
    }, 1000);
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
        console.log(e);
    }
})();


