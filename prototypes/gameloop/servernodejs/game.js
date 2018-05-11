exports.receiveGameData = function(req, res) {
    console.log(req.url)
    res.writeHead(200, {'Content-Type': 'application/json'})
    res.write("{}")
    return res.end();
  }