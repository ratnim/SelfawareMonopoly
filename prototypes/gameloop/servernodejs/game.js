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

  doAction(actionRequest) {
    var lastKnownId = 0
    if(actionRequest.action.hasOwnProperty(ActionFields.ID))
      lastKnownId = actionRequest.action[ActionFields.ID]

    switch(this.state) {
      case GameStates.SETUP:
        this.doSetupAction(actionRequest)
        break
      case GameStates.RUNNING:
        this.doIngameAction(actionRequest)
        break
      case GameStates.FINISHED:
        this.doReviewAction(actionRequest)
        break
    }

    if(actionRequest.hasOwnProperty(MessageFields.ERROR))
      return JSON.stringify({ "error" : actionRequest[MessageFields.ERROR]});

    var pastActions = this.getPassedActions(lastKnownId)
    return JSON.stringify(pastActions)
  }

  doSetupAction(actionRequest) {
    switch(actionRequest[MessageFields.ACTION][ActionFields.NAME]) {
      case ActionNames.ENTER_GAME:
        this.addPlayer(actionRequest)
        break
      case ActionNames.START_GAME:
        this.startGame(actionRequest)
        break
      default:
        actionRequest[MessageFields.ERROR] = "Action not supported while setup."
        break
    }
  }

  doIngameAction(actionRequest) {
    switch(actionRequest[MessageFields.ACTION][ActionFields.NAME]) {
      case ActionNames.ROLL_DICE:
        this.rollDice(actionRequest)
      break
      default:
        actionRequest[MessageFields.ERROR] = "Action not supported while ingame."
        break
    }
  }

  doReviewAction(actionRequest) {
    switch(actionRequest[MessageFields.ACTION][ActionFields.NAME]) {
      default:
        actionRequest[MessageFields.ERROR] = "Action not supported while review."
        break
    }
  }

  addPlayer(actionRequest) {
    if(this.state != GameStates.SETUP)
    {
      actionRequest[MessageFields.ERROR] = "Game has already started."
      return
    }

    if(!this.players.includes(actionRequest[MessageFields.PLAYER])){
      this.players.push(actionRequest[MessageFields.PLAYER])
    } else {
      actionRequest[MessageFields.ERROR] = "Player already exists."
    }
  }

  startGame(actionRequest) {
    if(this.state != GameStates.SETUP)
    {
      actionRequest[MessageFields.ERROR] = "Game is not in setup state."
      return
    }
    if(this.players.length < 2)
    {
      actionRequest[MessageFields.ERROR] = "At least 2 players are required."
      return
    }

    this.state = GameStates.RUNNING
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

  getPassedActions(sinceId) {
    return this.actions.slice(sinceId, this.actions.length)
  }

  rollDice(action) {
    if(this.getCurrentPlayer() != action[MessageFields.PLAYER])
    {
      action[MessageFields.ERROR] = "Not your turn."
      return
    }

    action[ActionFields.ID] = this.getId()
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
