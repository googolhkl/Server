const express = require('express');
const app = express();

app.set('views', './views');
app.set('view engine', 'pug');

app.use(express.static('public'));

app.get('/', function (req, res) {
	res.send("This is Send");

});

app.get('/template', function(req, res) {
	res.render('temp');

});

app.get('/login', function(req, res) {
	res.send("Please Login");
});

app.listen(3000, function() {
	console.log("Connected!");
});
