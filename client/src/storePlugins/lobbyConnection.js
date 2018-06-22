//websocket
var socket = undefined;
var createGameCallback = undefined;
var getGameListCallback = undefined;
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
  if (JSONObject.name == 'game_list') {
    getGameListCallback(JSONObject.data.games);
  } else if (JSONObject.name == 'create_game') {
    createGameCallback(JSONObject.data.game_id);
  } else if (JSONObject.error) {
    errorCallback(JSONObject.error.message);
  }
}


// Write functions
export function connect(sessionId) {
  socket = new WebSocket(process.env.VUE_APP_WEBSOCKET_URL + '/lobby?session=' + sessionId);

  socket.onmessage = function(event) {
    var JSONObject = JSON.parse(event.data);
    parseResponse(JSONObject);
  }
}

export function disconnect() {
  socket.close();
}

export function createGame(name) {
  var request = 'create_game';
  var data = { 'game_label' : name };

  socket.send(createJSON(request, data));
}

export function onCreateGame(callback) {
  createGameCallback = callback;
}

export function onGetGameList(callback) {
  getGameListCallback = callback;
}

export function onError(callback) {
  errorCallback = callback;
}
