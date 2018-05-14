var utils = require('./utils')

var ActionNames = Object.freeze({"rollDice":1, "startTurn":2, "endTurn":3})
var GameStates = Object.freeze({"setup":1, "running":2, "finished":3})

class Player {
  constructor(name) {
    this.name = name
  }
}


class Game {
  constructor() {
    this.state = GameStates.setup
    this.players = []
    this.actions = []
    this.current_players_turn
    this.next_id = 0
  }

  getId() {
    return this.next_id++
  }

  getCurrentPlayer() {
    return this.players[this.current_players_turn]
  }
  
  changePlayer() {
    this.current_players_turn += 1
    if(this.current_players_turn >= this.players.length)
    this.current_players_turn = 0
  }

  actionsSince(lastAction) {
    return actions.slice(lastAction)
  }

  doAction(action) {
    switch(this.state) {
      case GameStates.setup:
        this.doSetupAction(action)
        break
      case GameStates.running:
        this.doIngameAction(action)
        break
      case GameStates.finished:
        this.doReviewAction(action)
        break
    }

    return JSON.stringify(action)
  }

  doSetupAction(action) {
    switch(action["action"]["name"]) {
      case "enterGame":
        this.addPlayer(action)
        break
      case "startGame":
        this.startGame(action)
        break
      default:
        action["error"] = "Action not Supported will setup."
        break
    }
  }

  doIngameAction(action) {
    switch(action["action"]["name"]) {
      case "rollDice":
      this.rollDice(action)
      break
      default:
        action["error"] = "Action not Supported will ingame."
        break
    }
  }

  doReviewAction(action) {
    switch(action["action"]["name"]) {
      default:
        action["error"] = "Action not Supported will review."
        break
    }
  }

  addPlayer(action) {
    if(this.state != GameStates.setup)
    {
      action["error"] = "Game is already started."
      return
    }

    if(!this.players.includes(action["player"])){
      this.players.push(action["player"])
    } else {
      action["error"] = "Player already exists."
    }
  }

  startGame(action) {
    if(this.state != GameStates.setup)
    {
      action["error"] = "Game is not in setup state."
      return
    }
    if(this.players.length < 2)
    {
      action["error"] = "At least 2 players are required."
      return
    }

    this.state = GameStates.running
    this.current_players_turn = 0
    this.doPlayerStartTurn()
  }

  doPlayerStartTurn() {
    var action = {"player": this.getCurrentPlayer(),
              "id": this.getId(), 
              "action" : {"name" : "startTurn"}}
    this.signAction(action)
  }

  doPlayerEndTurn() {
    var action = {"player": this.getCurrentPlayer(),
              "id": this.getId(), 
              "action" : {"name" : "endTurn"}}
    this.signAction(action)
  }

  signAction(action) {
    utils.logAction(action)
    this.actions.push(action)
  }

  rollDice(action) {
    if(this.getCurrentPlayer() != action["player"])
    {
      action["error"] = "Not your turn."
      return
    }

    action["id"] = this.getId()
    var eyes1 = (Math.floor((Math.random() * 6) + 1))
    var eyes2 = (Math.floor((Math.random() * 6) + 1))
    action["eyes"] = [eyes1, eyes2]
    this.signAction(action)
    
    this.doPlayerEndTurn()
    this.changePlayer()
    this.doPlayerStartTurn()
  }
}

exports.Game = Game
exports.Player = Player
