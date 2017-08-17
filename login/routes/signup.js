const express = require('express');
const mysql = require('mysql');
const bkfd2Password = require('pbkdf2-password');
const config = require('../config.js');

const router = express.Router();

// DB 정보 불러오기
const db_info = {
	host: config.host,
	user: config.user,
	password: config.password,
	database: config.database
};
const connection = mysql.createConnection(db_info);

router.get('/signup', function(req, res) {
	res.render('signup', {});
});

router.post('/signup', function(req, res) {
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

module.exports = router;
