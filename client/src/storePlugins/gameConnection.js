//websocket
var socket = new WebSocket('ws://localhost:31415/');

// Helper
function createJSON(request, data) {
  var JSONObject = {
    'request' : request,
    'data' : data
  };
  return JSON.stringify(JSONObject, null, '\t');
}


// Write functions
function connect() {
  socket = new WebSocket('ws://localhost:31415');
}

function disconnect() {
  socket.close();
}

function joinGame() {
  var request = { 'request' : 'join_game' };

  socket.send(JSON.stringify(request));
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


// Read functions
function parseResponse(JSONObject) {
  if (JSONObject.name == 'possible_actions') {
    //store.commit('TODO', JSONObject.data);
  } else if (JSONObject.name == 'player_move') {
    //store.commit('TODO', JSONObject.data);
  } else if (JSONObject.name == 'end_game') {
    //store.commit('TODO');
  } else if (JSONObject.name == 'join_game') {
    //store.commit('TODO', JSONObject.data);
  } else if (JSONObject.name == 'player_ready') {
    //store.commit('TODO', JSONObject.data);
  } else if (JSONObject.name == 'game_start') {
    //store.commit('TODO');
  } else if (JSONObject.name == 'change_turn') {
    //store.commit('TODO', JSONObject.data);
  } else if (JSONObject.name == 'roll_dice') {
    //store.commit('TODO', JSONObject.data);
  } else if (JSONObject.name == 'error') {
    //store.commit('TODO', JSONObject.data);
  }
}


// Callback
socket.onmessage = function(event) {
  var JSONObject = JSON.parse(event.data);
  parseResponse(JSONObject);
}


// Store connections
export default function(store) {
  /*store.subscribe(mutation => {
    if (mutation.type === 'TODO') {
      joinGame();
    }
  })*/
  /*store.subscribe(mutation => {
    if (mutation.type === 'TODO') {
      setReady();
    }
  })*/
  /*store.subscribe(mutation => {
    if (mutation.type === 'TODO') {
      startGame();
    }
  })*/
  /*store.subscribe(mutation => {
    if (mutation.type === 'TODO') {
      endTurn();
    }
  })*/
  /*store.subscribe(mutation => {
    if (mutation.type === 'TODO') {
      rollDice();
    }
  })*/
}
