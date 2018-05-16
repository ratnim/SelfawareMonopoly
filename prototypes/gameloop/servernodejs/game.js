var utils = require('./utils')

var MessageFields = Object.freeze({"ACTION":"action", "PLAYER":"player", "ERROR":"error"})
var ActionFields = Object.freeze({"NAME":"name", "ID":"id"})
var ActionNames = Object.freeze({"ENTER_GAME":"enterGame", "START_GAME":"startGame", "STOP_GAME":"stopGame", "ROLL_DICE":"rollDice", "START_TURN":"startTurn", "END_TURN":"endTurn"})
var GameStates = Object.freeze({"SETUP":"setup", "RUNNING":"running", "FINISHED":"finished"})

class Player {
  constructor(name) {
    this.name = name
  }
}


class Game {
  constructor() {
    this.state = GameStates.SETUP
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

  doAction(message) {
    var lastKnownId = 0
    if(message.action.hasOwnProperty(ActionFields.ID))
      lastKnownId = message.action.id

    switch(this.state) {
      case GameStates.SETUP:
        this.doSetupAction(message)
        break
      case GameStates.RUNNING:
        this.doIngameAction(message)
        break
      case GameStates.FINISHED:
        this.doReviewAction(message)
        break
    }

    if(message.hasOwnProperty(MessageFields.ERROR))
      return JSON.stringify({ "error" : message.error});

    var pastActions = this.getPassedActions(lastKnownId)
    return JSON.stringify(pastActions)
  }

  doSetupAction(message) {
    switch(message.action.name) {
      case ActionNames.ENTER_GAME:
        this.addPlayer(message)
        break
      case ActionNames.START_GAME:
        this.startGame(message)
        break
      default:
        message.error = "Action not supported while setup."
        break
    }
  }

  doIngameAction(message) {
    switch(message.action.name) {
      case ActionNames.ROLL_DICE:
        this.rollDice(message)
      break
      default:
        message.error = "Action not supported while ingame."
        break
    }
  }

  doReviewAction(message) {
    switch(message.action.name) {
      default:
        message.error = "Action not supported while review."
        break
    }
  }

  addPlayer(message) {
    if(this.state != GameStates.SETUP)
    {
      message.error = "Game has already started."
      return
    }

    if(!this.players.includes(message.player)){
      this.players.push(message.player)
    } else {
      message.error = "Player already exists."
    }
  }

  startGame(message) {
    if(this.state != GameStates.SETUP)
    {
      message.error = "Game is not in setup state."
      return
    }
    if(this.players.length < 2)
    {
      message.error = "At least 2 players are required."
      return
    }

    this.state = GameStates.RUNNING
    this.current_players_turn = 0
    this.doPlayerStartTurn()
  }

  doPlayerStartTurn() {
    var action = {"player": this.getCurrentPlayer(),
              "action" : {"id": this.getId(), "name" : "startTurn"}}
    this.signAction(action)
  }

  doPlayerEndTurn() {
    var action = {"player": this.getCurrentPlayer(),
              "action" : {"id": this.getId(), "name" : "endTurn"}}
    this.signAction(action)
  }

  signAction(action) {
    utils.logAction(action)
    this.actions.push(action)
  }

  getPassedActions(sinceId) {
    return this.actions.slice(sinceId, this.actions.length)
  }

  rollDice(message) {
    if(this.getCurrentPlayer() != message.player)
    {
      message.error = "Not your turn."
      return
    }

    message.action.id = this.getId()
    var eyes1 = (Math.floor((Math.random() * 6) + 1))
    var eyes2 = (Math.floor((Math.random() * 6) + 1))
    message.action.eyes = [eyes1, eyes2]
    this.signAction(message)
    
    this.doPlayerEndTurn()
    this.changePlayer()
    this.doPlayerStartTurn()
  }
}

exports.Game = Game
exports.Player = Player
