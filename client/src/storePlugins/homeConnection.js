var socket = undefined;
var joinLobbyCallback = undefined;
var errorCallback = undefined;


function createJSON(request, data) {
  var JSONObject = {
    'request' : request,
    'data' : data
  };
  return JSON.stringify(JSONObject, null, '\t');
}

function parseResponse(JSONObject) {
  if (JSONObject.name == 'enter_lobby') {
    joinLobbyCallback(JSONObject.data.session);
  } else if (JSONObject.error) {
    errorCallback(JSONObject.error.message);
  }
}


export function connect() {
  socket = new WebSocket(process.env.VUE_APP_WEBSOCKET_URL);

  socket.onmessage = function(event) {
    var JSONObject = JSON.parse(event.data);
    parseResponse(JSONObject);
  }
}

export function disconnect() {
  socket.close();
}

export function createAccount(name) {
  var request = 'enter_lobby';
  var data = { 'player_name' : name };

  socket.send(createJSON(request, data));
}

export function onJoinLobby(callback) {
  joinLobbyCallback = callback;
}

export function onError(callback) {
  errorCallback = callback;
}
