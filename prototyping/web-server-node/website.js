const express = require('express');
const app = express();

app.use(express.static('public'));
app.use(express.json());

app.post('/api', (request, response) => {
    console.log('I got a request!');
    console.log(request.body);
})
