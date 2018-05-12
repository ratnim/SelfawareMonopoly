exports.createPlayer = function(req, res) {
  console.log(req.url)
  res.writeHead(200, {'Content-Type': 'application/json'})
  res.write("{}")
  return res.end();
}

exports.receiveGameData = function(req, res) {
    console.log(req.url)
    res.writeHead(200, {'Content-Type': 'application/json'})
    res.write("{}")
    return res.end();
  }

var ActionNames = Object.freeze({"rollDice":1, "startTurn":2, "endTurn":3})
var GameStates = Object.freeze({"setup":1, "running":2, "finished":3})

class Player {
  constructor(name) {
    this.name = name
  }
}

class Action {
  constructor(actionName) {
    this.name = actionName 
  }
}

class Game {
  constructor() {
    this.state = GameStates.setup
    this.players = []
    this.actions = []
  }

  get state() {
    return state
  }

  get players() {
    return players;
  }

  actionsSince(lastAction) {
    return actions.slice(lastAction)
  }

  addPlayer(player) {
    players.add(player)
  }

  doAction(action) {

  }
}