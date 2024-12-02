// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

// test.js

// Windows: Se necesita Python 2.7 y MSVC
//
// npm install -g node-gyp
//
// node-gyp configure
// node-gyp build
// node test.js


function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

// const kth = require('../lib/binding/Release/node-v57-win32-x64/kth-bch-native')         // Windows Fernando
const kth = require('../lib/binding/Release/node-v48-linux-x64/kth-bch-native')         // Linux Fernando

var express = require('express')
, app = express()
// , sse = require('./sse')

// const app = express()
const port = 8080

process.stdin.resume();//so the program will not close instantly

// app.use(sse)

// var connections = []

process.on("SIGINT", function () {
    console.log("captured SIGINT...");
    // kth.node_destruct(node)
    process.exit();
});

process.on("exit", function () {
    console.log("on exit");
    // exec.close()
});

const node = kth.node_construct("", process.stdout, process.stderr);
// const node = kth.node_construct("", null, null)
kth.node_initchain(node)
kth.node_run_wait(node)

const chain = kth.node_get_chain(node)

var last_height = 0

kth.chain_subscribe_blockchain(node, chain, function (e, fork_height, blocks_incoming, blocks_replaced) {
    if (e == 0) {
        for (clientId in clients) {
            clients[clientId].write("event: time\n" + "data: " + fork_height + "\n\n");
        };
    } else {
        // console.log(`chain_subscribe_blockchain failed, err: ${e}, fork_height: ${fork_height}, blocks_incoming: ${blocks_incoming}, blocks_replaced: ${blocks_replaced}`)
        console.log(`chain_subscribe_blockchain failed, err: ${e}, fork_height: ${fork_height}`)
    }
    return true
})

app.get('/', (request, response) => {
    // response.send('Hello from Express!')
    response.send(`<!DOCTYPE html>
    <html>
     <head>
      <title>Server-sent events test</title>
      <style>html,body,#test{height:98%;}</style>
     </head>
     <body>
      <script type="text/javascript">
        document.addEventListener('DOMContentLoaded', function () {
          var source = new EventSource('last_height');
          source.addEventListener('time', function (event) {
            document.getElementById('lblHeight').innerHTML = event.data;
          });
          source.addEventListener('error', function (event){
            console.log('SSE error:', event);
            console.log('SSE state:', source.readyState);
          });
        }, false);
      </script>
      Last Block Height: <label id="lblHeight">0</label>
     </body>
    </html>`)
})

var clientId = 0;
var clients = {}; // <- Keep a map of attached clients

app.get('/last_height/', function(req, res) {
    // console.log(`last_height Infinity: ${Infinity}`)
    console.log(`last_height Number.MAX_VALUE: ${Number.MAX_VALUE}`)
    // req.socket.setTimeout(Infinity);
    req.socket.setTimeout(Number.MAX_VALUE);

    res.writeHead(200, {
    	'Content-Type': 'text/event-stream',  // <- Important headers
    	'Cache-Control': 'no-cache',
    	'Connection': 'keep-alive'
    });

    res.write('\n');
    (function(clientId) {
        clients[clientId] = res;  // <- Add this client to those we consider "attached"
        req.on("close", function(){delete clients[clientId]});  // <- Remove this client when he disconnects
    })(++clientId)
});

app.listen(port, (err) => {
    if (err) {
        return console.log('something bad happened', err)
    }

    console.log(`server is listening on ${port}`)
})
