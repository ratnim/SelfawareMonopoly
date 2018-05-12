var game = require('./game')
var utils = require('./utils')

var games = []

exports.handleRequest = function(req, res) {
    var route = utils.getRoute(req)
  
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