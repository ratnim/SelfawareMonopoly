
//websocket

// Helper
function createJSON(request, data) {
  var JSONObject = {
    'request' : request,
    'data' : data
  };
  return JSON.stringify(JSONObject, null, '\t');
}

export default class HomeConnection {
  constructor(eventHandlers) {
    //session id is a string required for the socket connection
    //eventHandlers is a dictionary with event name as key and functions as values
    // e.g. eventHandlers = {enter_lobby: (data) => console.log(data)}
    this.socket = new WebSocket(process.env.VUE_APP_WEBSOCKET_URL);
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

  createAccount(name) {
    var request = 'enter_lobby';
    var data = { 'player_name' : name };

    this.socket.send(createJSON(request, data));
  }
}
