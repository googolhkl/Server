const express = require('express');
const app = express();
app.locals.pretty = true; // jade로 생성되는 코드가 보기 좋도록
app.set('views', './views');
app.set('view engine', 'pug');

app.use(express.static('public'));

app.get('/', function (req, res) {
	res.send("This is Send");

});

app.get('/template', function(req, res) {
	res.render('temp', {time: Date(), title: 'googolhkl'});

});

app.get('/login', function(req, res) {
	res.send("Please Login");
});

app.listen(3000, function() {
	console.log("Connected!");
});
