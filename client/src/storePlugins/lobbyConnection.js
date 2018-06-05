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

function createGame(name) {
  var request = 'create_game';
  var data = { 'game_label' : name };

  socket.send(createJSON(request, data));
}


// Read functions
function parseResponse(JSONObject) {
  if (JSONObject.name == 'game_list') {
    store.commit('setGameList', JSONObject.data);
  } else if (JSONObject.name == 'create_game') {
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
      createGame(mutation.payload);
    }
  })*/
}
