//DATA//
var games = [{
    'game_label': 'HPIler',
    'game_id': '1337',
    'player_list': ['Martina', 'Marc','Jannina'],
    'game_status' : ''
  },
  {
    'game_label': 'HPIler',
    'game_id': '1338',
    'player_list': ['Pascale', 'Konstanze'],
    'game_status' : ''
  }
];



var server = require('http').createServer();
var io = require('socket.io')(server);
var port = process.env.PORT || 3000;

server.listen(port, () => {
  console.log('Server listening at port %d', port);
});


io.on('connection', (socket) => {
  console.log('new connection');

  setInterval(function() {
    console.log("send gamelist");
    socket.broadcast.emit('game_list', games);
  }, 2000);

  // when the client emits 'new message', this listens and executes
  socket.on('new message', (data) => {
    // we tell the client to execute 'new message'
    socket.broadcast.emit('new message', {
      username: socket.username,
      message: data
    });
  });

  // when the client emits 'add user', this listens and executes
  socket.on('enter_lobby', (username) => {

    socket.broadcast.emit('user joined', {
      username: username
    });
  });

  // when the client emits 'typing', we broadcast it to others
  socket.on('typing', () => {
    socket.broadcast.emit('typing', {
      username: socket.username
    });
  });

  // when the client emits 'stop typing', we broadcast it to others
  socket.on('stop typing', () => {
    socket.broadcast.emit('stop typing', {
      username: socket.username
    });
  });

  // when the user disconnects.. perform this
  socket.on('disconnect', () => {
  });
});
