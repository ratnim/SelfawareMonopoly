var http = require('http');
var url = require('url')

var fileHandler = require('./staticfilehandler');
var game = require('./game');

var returnBadRequest = function(req, res) {
  res.writeHead(400, {'Content-Type': 'text/html'})
  res.write("<html><body>Bad Request</body></html>")
  return res.end();
}

var getRoute = function(req) {
  var url_parts = url.parse(req.url)
  return url_parts.pathname
}

var handleGET = function(req, res) {
  var route = getRoute(req)

  switch (route) {
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
  var route = getRoute(req)

  switch (route) {
    case '/lobby':
      game.createPlayer(req, res)
      break
    case '/game':
      game.receiveGameData(req, res)
      break
    default:
      returnBadRequest(req, res);
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