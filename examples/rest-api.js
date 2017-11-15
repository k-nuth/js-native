// test.js

// Windows: Se necesita Python 2.7 y MSVC
//
// npm install -g node-gyp
//
// node-gyp configure
// node-gyp build
// node test.js


// const bitprim = require('./bitprim.js');
// const express = require('express')

var express = require('express')
, app = express()
, sse = require('./sse')


// const app = express()
const port = 8080

process.stdin.resume();//so the program will not close instantly

// // const exec = bitprim.open("/home/fernando/exec/btc-mainnet.cfg")
// const exec = bitprim.openWithStd("/home/fernando/exec/btc-mainnet.cfg")

// var res = exec.initchain()
// // console.log(`res: ${res}`)
// res = exec.run_wait()
// // console.log(`res: ${res}`)

// if (res != 0) {
//     exec.close()
//     process.exit();
// }

app.use(sse)



var connections = []

process.on("SIGINT", function () {
    console.log("captured SIGINT...");
    process.exit();
});


process.on("exit", function () {
    // console.log("on exit");
    // exec.close()
});


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

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}


app.get('/last_height', function(req, res) {
    console.log('/last_height')
    res.sseSetup()

    for (var i = 0; i < 10; i++) {
        res.sseSend(i)

        // await sleepFer(2000);
        // Usage!
        sleep(500).then(() => {
            // Do something after the sleep!
        });        
    }
    // res.sseSend(votes)

    connections.push(res)
})

//     @cherrypy.expose
//     def last_height(self):
//         cherrypy.response.headers["Content-Type"] = "text/event-stream"
//         def generator():
//             while True:
//                 event.wait()
//                 yield "event: time\n" + "data: " + str(last_height) + "\n\n"
//                 event.clear()
//         return generator()

//     last_height._cp_config = {'response.stream': True}


// app.get('/validate-tx/:txhex', function(request, response) {

//     var txhex = request.params.txhex; //or use request.param('txhex')
//     console.log(`validate_tx request txhex: ${txhex}`)

//     exec.validate_tx(txhex, function (err, message) {
//         console.log(`validate_tx callback - err: ${err}, message: ${message}`)
//         response.send(`validate_tx callback - err: ${err}, message: ${message}`)
//     })
// })

app.listen(port, (err) => {
    if (err) {
        return console.log('something bad happened', err)
    }

    console.log(`server is listening on ${port}`)
})





// import os
// import sys
// import threading
// import cherrypy
// import bitprim

// event = threading.Event()
// last_height = 0

// class BlockHandler(object):
//     def __init__(self, executor):
//         self.executor = executor

//     # A typical reorganization consists of one incoming and zero outgoing blocks.
//     def __call__(self, ec, fork_height, incoming, outgoing):
//         if self.executor.stopped or ec == 1:
//             event.clear()
//             return False

//         if ec != 0:
//             event.clear()
//             self.executor.stop()
//             return False

//         #  Nothing to do here.
//         if not incoming or incoming.count == 0:
//             event.clear()
//             return True

//         global last_height
//         last_height = fork_height
//         event.set()
//         # print(last_height)
//         return True

// class Root():

//     @cherrypy.expose
//     def index(self):
//         return r'''<!DOCTYPE html>
// <html>
//  <head>
//   <title>Server-sent events test</title>
//   <style>html,body,#test{height:98%;}</style>
//  </head>
//  <body>
//   <script type="text/javascript">
//     document.addEventListener('DOMContentLoaded', function () {
//       var source = new EventSource('last_height');
//       source.addEventListener('time', function (event) {
//         document.getElementById('lblHeight').innerHTML = event.data;
//       });
//       source.addEventListener('error', function (event){
//         console.log('SSE error:', event);
//         console.log('SSE state:', source.readyState);
//       });
//     }, false);
//   </script>
//   Last Block Height: <label id="lblHeight">0</label>
//  </body>
// </html>'''

//     @cherrypy.expose
//     def last_height(self):
//         cherrypy.response.headers["Content-Type"] = "text/event-stream"
//         def generator():
//             while True:
//                 event.wait()
//                 yield "event: time\n" + "data: " + str(last_height) + "\n\n"
//                 event.clear()
//         return generator()

//     last_height._cp_config = {'response.stream': True}


// def main():
//     # execut = bitprim.Executor("/home/fernando/execution_tests/btc_mainnet.cfg", sys.stdout, sys.stderr)
//     with bitprim.Executor("/home/fernando/execution_tests/btc_mainnet.cfg", sys.stdout, sys.stderr) as execut:

//         if not os.path.isdir("./blockchain"):
//             res = execut.init_chain()
//             print(res)

//         res = execut.run_wait()
//         if not res:
//             return

//         # execut.chain.subscribe_blockchain(subscribe_blockchain_handler)
//         execut.chain.subscribe_blockchain(BlockHandler(execut))

//         # ----------------------------------------------------------------------------------------------------
//         cherrypy.config.update({'server.socket_host': '0.0.0.0', 'server.socket_port': 8080,})
//         cherrypy.quickstart(Root())
//         # ----------------------------------------------------------------------------------------------------

//     # execut._destroy()

// if __name__ == '__main__':
//     main()


