var game = require('./game')
var utils = require('./utils')

var games = []

handleAction = function(res, action) {
  var game_instance = getGame()
  var msg = game_instance.doAction(action);
  utils.returnOKRequest(res, msg)
}

parseRequest = function(req, res) {
  let body = '';

  req.on('data', (chunk) => {
    body += chunk.toString()
  })
  req.on('end', () => {
    var action = JSON.parse(body)
    handleAction(res, action)
  });
}

getGame = function() {
  if(games.length == 0)
    games.push(new game.Game())
  return games[0];
} 

exports.handleRequest = function(req, res) {
  var route = utils.getRoute(req)

  switch (route) {
    case '/lobby':
    case '/game':
      parseRequest(req, res)
      break
    default:
      returnBadRequest(req, res);
      break;
  }
}
