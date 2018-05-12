var fs = require('fs');

var utils = require('./utils')

var folder = '../client/'
var lobbyFile = folder + './lobby.html'
var gameFile = folder + '/game.html'

returnFile = function(req, res, file) {
    fs.readFile(file, function(err, data) {
        if (err) {
            throw err;
        }

        res.writeHead(200, {'Content-Type': 'text/html'});
        res.write(data);
        return res.end();
      });
}

exports.handleRequest = function(req, res) {
    var route = utils.getRoute(req)
  
    switch (route) {
      case '/':          
      case '/lobby':
        returnFile(req, res, lobbyFile)
      break
      case '/game':
        returnFile(req, res, gameFile)
        break
      default:
        utils.returnBadRequest(req, res)
        break
    }
  }