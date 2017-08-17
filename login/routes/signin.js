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

router.get('/signin', function(req, res) {
	res.render('signin', {});
});

router.post('/signin', function(req, res) {
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

module.exports = router;
