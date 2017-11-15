module.exports = function (req, res, next) {
    res.sseSetup = function() {
      res.writeHead(200, {
        'Content-Type': 'text/event-stream',
        'Cache-Control': 'no-cache',
        'Connection': 'keep-alive'
      })
    }
  
    res.sseSend = function(data) {
    //   res.write("data: " + JSON.stringify(data) + "\n\n");
      var xxx = "event: time\n" + "data: " + data + "\n\n"
      console.log(xxx)
      res.write(xxx);
    //   yield "event: time\n" + "data: " + str(last_height) + "\n\n"

    }
  
    next()
  }