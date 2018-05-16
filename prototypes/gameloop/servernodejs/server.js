var http = require('http')

var fileHandler = require('./staticfilehandler')
var gameHandler = require('./gamehandler')

http.createServer(function (req, res) {
    switch (req.method) {
      case 'GET':
        fileHandler.handleRequest(req, res)
        break
      case 'POST':
        gameHandler.handleRequest(req, res)
        break
      default:
        returnBadRequest(req, res)
        break
    }

}).listen(8080);
