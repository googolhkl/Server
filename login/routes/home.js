const express = require('express');
const router = express.Router()

// 홈
router.get('/', function (req, res) {
	res.render('home', {});
});

module.exports = router
