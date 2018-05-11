var fs = require('fs');

exports.returnLobby = function(req, res) {
    fs.readFile('../client/lobby.html', function(err, data) {
        res.writeHead(200, {'Content-Type': 'text/html'});
        res.write(data);
        return res.end();
      });
}

exports.returnGame = function(req, res) {
    fs.readFile('../client/Game.html', function(err, data) {
        res.writeHead(200, {'Content-Type': 'text/html'});
        res.write(data);
        return res.end();
      });
}