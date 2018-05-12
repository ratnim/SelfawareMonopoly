var game = require('./game')
var utils = require('./utils')

var games = []

parseRequest = function(req, res) {
  let body = '';
  let waiting = true

  req.on('data', (chunk) => {
    body += chunk.toString()
  })
  req.on('end', () => {
    waiting = false
    utils.logAction(body)
    utils.returnOKRequest(res, "{}")
  });
}

game = function() {
  if(games.length == 0)
    games.push(new game.Game())
  return games[0];
} 

exports.handleRequest = function(req, res) {
  var route = utils.getRoute(req)

  switch (route) {
    case '/lobby':
    case '/game':
      var action = parseRequest(req, res)
      break
    default:
      returnBadRequest(req, res);
      break;
  }
}