const express = require('express');
const hello = require('./build/Release/hello');
const fib = require('./build/Release/fib');
const bodyParser = require('body-parser');
const morgan = require('morgan');

const codeWord = require('./build/Release/codeWord');


const app = express();


const PORT = 3000 || env.process.PORT;

app.listen(PORT, console.log(`Server is running on port ${PORT}`));

app.use(express.static('public'));

app.set('view engine', 'ejs');
app.use(morgan('dev'));

app.use(bodyParser.urlencoded({extended: true}));
app.use(bodyParser.json());


app.get('/', (req, res) => {
    res.render('index', {word: "initialize your word"});
})

app.post('/', (req, res) => {
    let {word, cryptStep, codeType} = req.body;
    if(codeType == "code") {
        res.render('index', {word: codeWord.codeWord(word.toLowerCase(), parseInt(Math.round(cryptStep)))});
    } 
    if(codeType == "decode") {
        res.render('index', {word: codeWord.decodeWord(word.toLowerCase(), parseInt(Math.round(cryptStep)))});
    }
});
