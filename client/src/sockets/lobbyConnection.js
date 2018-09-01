

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

export default class LobbyConnection {
  constructor(sessionId, eventHandlers) {
    //session id is a string required for the socket connection
    //eventHandlers is a dictionary with event name as key and functions as values
    // e.g. eventHandlers = {game_list: (data) => console.log(data)}
    this.socket = new WebSocket(process.env.VUE_APP_WEBSOCKET_URL + '/lobby?session=' + sessionId);
    this.sessionId = sessionId;
    this.eventHandlers = eventHandlers;
    this.socket.onmessage = (event) => this.handleResponse(event);
  }

  handleResponse(event) {
    var JSONObject = JSON.parse(event.data);
    if (this.eventHandlers.hasOwnProperty(JSONObject.name)) {
      this.eventHandlers[JSONObject.name](JSONObject.data);
    } else {
      console.error("Missing event handler for event ", event);
    }
  }

  disconnect() {
    this.socket.close();
  }

  createGame(name) {
    var request = 'create_game';
    var data = { 'game_label' : name };

    this.socket.send(createJSON(request, data));
  }
}
