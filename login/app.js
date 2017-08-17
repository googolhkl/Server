const express = require('express');
const bodyParser = require('body-parser');

const routerHome = require('./routes/home');
const routerSignIn = require('./routes/signin');
const routerSignUp = require('./routes/signup');

const app = express();

app.locals.pretty = true; // jade로 생성되는 코드가 보기 좋도록

app.set('views', './views');
app.set('view engine', 'pug');

app.use(express.static('public'));
app.use(bodyParser.urlencoded({ extended: false }));  // POST 요청시 Body를 생성하기 위한 모듈

// 라우터 설정
app.use('/', routerHome);
app.use('/', routerSignIn);
app.use('/', routerSignUp);


app.listen(3000, function() {
	console.log("Connected!");
});

