var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'the test site' });
  console.log("get home page");
});

/* GET features page. */
router.get('/features', function(req, res, next) {
  //res.send("features");
  res.render('features', { title: 'the test site' });
  console.log("get features page");
});

module.exports = router;
