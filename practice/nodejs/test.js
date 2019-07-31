const http = require('http');

const hostname = '127.0.0.1';
const port = 3000;

const server = http.createServer((req, res) => {
  res.statusCode = 200;
  res.setHeader('Content-Type', 'text/plain');
  //res.end('Hello World\n');
  res.end('hey\n');
});

server.listen(port, hostname, () => {
  console.log(`Server running at http://${hostname}:${port}/`);
});

console.log("sup");

var express = require("express");
var app = express();

app.get("/", function(req, res){
    res.send("Hi there!");
    res.send("hey");
});

app.listen(process.env.PORT, process.env.IP, function(){
    console.log("double sup");
});