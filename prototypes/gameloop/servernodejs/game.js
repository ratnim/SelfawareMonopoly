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

exports.Game = Game
exports.Action = Action
exports.Player = Player