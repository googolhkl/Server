const mysql = require('mysql');
const express = require('express');
const bodyParser = require('body-parser');
const bkfd2Password = require('pbkdf2-password');
const config = require('./config.js');

// DB 정보 불러오기
const db_info = {
	host: config.host,
	user: config.user,
	password: config.password,
	database: config.database
};

const app = express();
const connection = mysql.createConnection(db_info);

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
	// 해당 아이이에 일치하는 유저 검색
	let salt;
	let login_id = req.body.login_id;
	let password = req.body.password;
	let query = 'SELECT * FROM users WHERE username=?';

	connection.query(query, [login_id], (err, results) => {
		if(err) {
			res.status(500);
			res.send({});
		} else {
			if(results[0]) { // 아이디가 존재할 때
				salt = results[0].salt;

				let hasher = bkfd2Password();
				hasher({password: password, salt: salt}, (err, password, salt, hash) => {
					query = 'SELECT * FROM users WHERE username=? AND password=?';
					connection.query(query, [login_id, hash], (err, results) => {
						if(err) {
							res.status(500);
							res.send({});
						} else {
							if(results[0]) {  // 비밀번호 일치 시
								res.send({
									"id": results[0].id,
									"userName": results[0].username,
									"nickName": results[0].nickName,
								});
							} else {  // 비밀번호 불일치 시
								res.status(400);
								res.send({});
							}
						}
					});
				});
			} else { // 아이디가 존재하지 않을 때
				res.status(400);
				res.send({});
			}
		}
	});
})

// 회원가입
app.get('/signup', function(req, res) {
	res.render('signup', {});
});
app.post('/signup', function(req, res) {
	// 비밀번호 암호화
	var hasher = bkfd2Password();
	hasher({password: req.body.password}, (err, password, salt, hash) => {
		let login_id = req.body.login_id;
		let nickname = req.body.nickname;
		let user = {
			authMethod: 'local:' + login_id,
			username: login_id,
			password: hash,
			salt: salt,
			nickName: nickname
		}

		// DB에 유저 생성
		let query = 'INSERT INTO users SET ?';
		connection.query(query, user, (err, results) => {
			if(err) {
				res.status(500);
				res.send("회원 가입 실패"); // 아이디, 닉네임 중복등
			} else {
				res.send("회원 가입 성공");
			}
		});
	});
});

app.listen(3000, function() {
	console.log("Connected!");
});

