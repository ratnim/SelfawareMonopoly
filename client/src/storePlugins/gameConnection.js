//websocket
var socket = undefined;
var diceRolledCallback = undefined;
var playerJoinedCallback = undefined;
var playerMovedCallback = undefined;
var playerReadyCallback = undefined;
var gameStartedCallback = undefined;
var gameEndedCallback = undefined;
var turnChangedCallback = undefined;
var errorCallback = undefined;

// Helper
function createJSON(request, data) {
  var JSONObject = {
    'request' : request,
    'data' : data
  };
  return JSON.stringify(JSONObject, null, '\t');
}

function parseResponse(JSONObject) {
  if (JSONObject.name == 'possible_actions') {
    console.log(JSONOBject);
  } else if (JSONObject.name == 'player_move') {
    playerMovedCallback(JSONObject.data.player_name, JSONObject.data.distance);
  } else if (JSONObject.name == 'end_game') {
    gameEndedCallback();
  } else if (JSONObject.name == 'join_game') {
    playerJoinedCallback(JSONObject.data.player_name);
  } else if (JSONObject.name == 'player_ready') {
    playerReadyCallback(JSONObject.data.player_name);
  } else if (JSONObject.name == 'game_start') {
    gameStartedCallback();
  } else if (JSONObject.name == 'change_turn') {
    turnChangedCallback(JSONObject.data.player_name);
  } else if (JSONObject.name == 'roll_dice') {
    diceRolledCallback(JSONObject.data.eyes);
  } else if (JSONObject.error) {
    errorCallback(JSONObject.error.message);
  }
}


// Write functions
export function connect(gameId, sessionId) {
  socket = new WebSocket('ws://localhost:31415/game?game_id=' + gameId + '&session=' + sessionId);

  socket.onmessage = function(event) {
    var JSONObject = JSON.parse(event.data);
    parseResponse(JSONObject);
  }
}

export function disconnect() {
  socket.close();
}

export function joinGame() {
  var request = { 'request' : 'join_game' };

  if (socket.readyState == 1) {
    socket.send(JSON.stringify(request)); 
  } else {
    socket.onopen = function() {
      socket.send(JSON.stringify(request));
    }
  }
}

export function setReady() {
  var request = { 'request' : 'player_ready' };

  socket.send(JSON.stringify(request));
}

export function startGame() {
  var request = { 'request' : 'game_start' };

  socket.send(JSON.stringify(request));
}

export function endTurn() {
  var request = { 'request' : 'end_turn' };

  socket.send(JSON.stringify(request));
}

export function rollDice() {
  var request = { 'request' : 'roll_dice' };

  socket.send(JSON.stringify(request));
}

export function onDiceRolled(callback) {
  diceRolledCallback = callback;
}

export function onPlayerJoined(callback) {
  playerJoinedCallback = callback;
}

export function onPlayerMoved(callback) {
  playerMovedCallback = callback;
}

export function onPlayerReady(callback) {
  playerReadyCallback = callback;
}

export function onGameStarted(callback) {
  gameStartedCallback = callback;
}

export function onGameEnded(callback) {
  gameEndedCallback = callback;
}

export function onTurnChanged(callback) {
  turnChangedCallback = callback;
}

export function onError(callback) {
  errorCallback = callback;
}

