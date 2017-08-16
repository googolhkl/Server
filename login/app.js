const express = require('express');
const bodyParser = require('body-parser');
const app = express();

app.locals.pretty = true; // jade로 생성되는 코드가 보기 좋도록

app.set('views', './views');
app.set('view engine', 'pug');

app.use(express.static('public'));
app.use(bodyParser.urlencoded({ extended: false }));  // POST 요청시 Body를 생성하기 위한 모듈

// 홈
app.get('/', function (req, res) {
	res.render('home', {});
});


// 로그인
app.get('/signin', function(req, res) {
	res.render('signin', {});
});
app.post('/signin', function(req, res) {
	// TODO: DB에서 검사
	res.send("로그인 성공");

})

// 회원가입
app.get('/signup', function(req, res) {
	res.render('signup', {});
});
app.post('/signup', function(req, res) {
	// TODO: DB에 추가하는 작업 필요
	let login_id = req.body.login_id;
	let password = req.body.password;
	let nickname = req.body.nickname;

	console.log(login_id, password, nickname);
	res.send("회원 가입 성공")
});



app.listen(3000, function() {
	console.log("Connected!");
});

