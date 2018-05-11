var http = require('http');

var fileHandler = require('./staticfilehandler');
var game = require('./game');

var returnBadRequest = function(req, res) {
  res.writeHead(400, {'Content-Type': 'text/html'})
  res.write("<html><body>Bad Request</body></html>")
  return res.end();
}

var handleGET = function(req, res) {
  var url = req.url

  switch (url) {
    case '/':          
    case '/lobby':
      fileHandler.returnLobby(req, res)
    break
    case '/game':
      fileHandler.returnGame(req, res)
      break
    default:
      returnBadRequest(req, res)
      break
  }
}

var handlePOST = function(req, res) {
  var url = req.url

  switch (url) {
    default:
      game.receiveGameData(req, res);
      break;
  }
}

http.createServer(function (req, res) {
    switch (req.method) {
      case 'GET':
        handleGET(req, res)
        break
      case 'POST':
        handlePOST(req, res)
        break
      default:
        returnBadRequest(req, res)
        break

    }

}).listen(8080);