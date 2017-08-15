const express = require('express');
const bodyParser = require('body-parser');
const app = express();

app.locals.pretty = true; // jade로 생성되는 코드가 보기 좋도록

app.set('views', './views');
app.set('view engine', 'pug');

app.use(express.static('public'));
app.use(bodyParser.urlencoded({ extended: false }));  // POST 요청시 Body를 생성하기 위한 모듈

app.get('/', function (req, res) {
	res.send("This is Send");

});

app.get('/template', function(req, res) {
	res.render('temp', {time: Date(), title: 'googolhkl'});

});

app.get('/login', function(req, res) {
	res.render('login', {});
});

app.post('/login', function(req, res) {
	res.send(req.body.title + ', ' + req.body.description);
});

app.listen(3000, function() {
	console.log("Connected!");
});
