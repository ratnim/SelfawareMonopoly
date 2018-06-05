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

function createAccount(name) {
  var request = 'enter_lobby';
  var data = { 'player_name' : name };

  socket.send(createJSON(request, data));
}


// Read functions
function parseResponse(JSONObject) {
  if (JSONObject.name == 'enter_lobby') {
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
  store.subscribe(mutation => {
    if (mutation.type === 'setNickname') {
      createAccount(mutation.payload);
    }
  })
}
