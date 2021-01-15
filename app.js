const express = require('express');
const hello = require('./build/Release/hello');

const app = express();


const PORT = 3000 || env.process.PORT;

app.listen(PORT, console.log(`Server is running on port ${PORT}`));

console.log(hello.hello());