//websocket

// Helper
function createJSON(request, data) {
  var JSONObject = {
    'request': request,
    'data': data
  };
  return JSON.stringify(JSONObject, null, '\t');
}

export default class GameConnection {
  constructor(sessionId, gameId, eventHandlers) {
    //session id is a string required for the socket connection
    //eventHandlers is a dictionary with event name as key and functions as values
    // e.g. eventHandlers = {enter_lobby: (data) => console.log(data)}
    this.socket = new WebSocket(process.env.VUE_APP_WEBSOCKET_URL + '/game?game_id=' + gameId + '&session=' + sessionId);
    this.eventHandlers = eventHandlers;
    this.socket.onmessage = (event) => this.handleResponse(event);
    if (this.socket.readyState == 1) {
        this.joinGame();
        this.requestGameboard();
      } else {
        this.socket.onopen = () => {
          this.joinGame();
          this.requestGameboard();
        }
      }
  }

  handleResponse(event) {
    var JSONObject = JSON.parse(event.data);
    if (this.eventHandlers.hasOwnProperty(JSONObject.name)) {
      this.eventHandlers[JSONObject.name](JSONObject.data);
    } else if (this.eventHandlers.hasOwnProperty("fallback")) {
      this.eventHandlers["fallback"](JSONObject.data);
    } else {
      console.error("Missing event handler for event ", event.data);
    }
  }

  disconnect() {
    this.socket.close();
  }

  requestGameboard() {
    var request = 'game_board';
    this.socket.send(createJSON(request, {}));
  }

  joinGame() {
    var request = 'join_game';
    this.socket.send(createJSON(request, {}));
  }

  setReady() {
    this.socket.send(createJSON('player_ready', {}));
  }

  startGame() {
    this.socket.send(createJSON('game_start', {}));
  }

  endTurn() {
    this.socket.send(createJSON('end_turn', {}));
  }

  rollDice() {
    this.socket.send(createJSON('roll_dice', {}));
  }
}


//
// function parseResponse(JSONObject) {
//   if (JSONObject.name == 'possible_actions') {
//     console.log(JSONOBject);
//   } else if (JSONObject.name == 'player_move') {
//     playerMovedCallback(JSONObject.data.player_name, JSONObject.data.distance);
//   } else if (JSONObject.name == 'end_game') {
//     gameEndedCallback();
//   } else if (JSONObject.name == 'join_game') {
//     playerJoinedCallback(JSONObject.data.player_name);
//   } else if (JSONObject.name == 'player_ready') {
//     playerReadyCallback(JSONObject.data.player_name);
//   } else if (JSONObject.name == 'game_start') {
//     gameStartedCallback();
//   } else if (JSONObject.name == 'change_turn') {
//     turnChangedCallback(JSONObject.data.player_name);
//   } else if (JSONObject.name == 'roll_dice') {
//     diceRolledCallback(JSONObject.data.eyes);
//   } else if (JSONObject.error) {
//     errorCallback(JSONObject.error.message);
//   }
// }
