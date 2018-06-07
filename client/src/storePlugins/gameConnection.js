//websocket
var socket = undefined;
var playerJoinedCallback = undefined;
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
    //store.commit('TODO', JSONObject.data);
  } else if (JSONObject.name == 'player_move') {
    //store.commit('TODO', JSONObject.data);
  } else if (JSONObject.name == 'end_game') {
    //store.commit('TODO');
  } else if (JSONObject.name == 'join_game') {
    playerJoinedCallback(JSONObject.data);
  } else if (JSONObject.name == 'player_ready') {
    //store.commit('TODO', JSONObject.data);
  } else if (JSONObject.name == 'game_start') {
    //store.commit('TODO');
  } else if (JSONObject.name == 'change_turn') {
    //store.commit('TODO', JSONObject.data);
  } else if (JSONObject.name == 'roll_dice') {
    //store.commit('TODO', JSONObject.data);
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

function setReady() {
  var request = { 'request' : 'player_ready' };

  socket.send(JSON.stringify(request));
}

function startGame() {
  var request = { 'request' : 'game_start' };

  socket.send(JSON.stringify(request));
}

function endTurn() {
  var request = { 'request' : 'end_turn' };

  socket.send(JSON.stringify(request));
}

function rollDice() {
  var request = { 'request' : 'roll_dice' };

  socket.send(JSON.stringify(request));
}

export function onPlayerJoined(callback) {
  playerJoinedCallback = callback;
}

export function onError(callback) {
  errorCallback = callback;
}

