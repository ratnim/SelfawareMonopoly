var url = require('url')

exports.returnBadRequest = function(req, res) {
  res.writeHead(400, {'Content-Type': 'text/html'})
  res.write("<html><body>Bad Request</body></html>")
  return res.end();
}

exports.returnOKRequest = function(res, content){
  res.writeHead(200, {'Content-Type': 'application/json'})
  res.write(content)
  return res.end();
}

exports.getRoute = function(req) {
  var url_parts = url.parse(req.url)
  return url_parts.pathname
}

exports.logAction = function(action) {
  console.log(action)
}
