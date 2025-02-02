// Import Node.js core module i.e http
const http = require('http');

// Create web server
const server = http.createServer(function (req, res) {
  if (req.method == 'POST') {
    console.log("POST request");
    res.end('recieved post request');
  } else {
      // Check the URL of the current request
      if (req.url == '/') {

        // Set response header
        res.writeHead(200, { 'Content-Type': 'text/html' });

        // Set response content    
        res.write(
            `<html lang="en">
              <head>
                <meta charset="UTF-8">
                <meta name="viewport" content="width=device-width, initial-scale=1.0">
                <link href="website.css" rel="stylesheet" type="text/css">
                <title> Self-Caring Plant </title>
              </head>
              <body>

              <nav class = "navbar" >
              <div class = "logo" ><a href="#">Self-Caring Plant</a></div>
              <ul> 
                <li><a href="/">Home</a></li>
                <li><a href="/camera">Camera</a></li>
                <li><a href="/about">About</a></li>
              </ul></nav>
              <div class = "flexbox-container" > 
              <p> Ideal Soil Moisture: </p>  
              <p> Stage of Plant: </p>
              <p> Water frequency: </p>
              <p> Lacking Nutrients: </p>
              <p> Nutrients being absorbed: </p>
        </div><script src="website.js"></script><body></html>`);
        res.end();//end the response
    } else if (req.url == "/camera") {

        res.writeHead(200, { 'Content-Type': 'text/html' });
        res.write(`
        <html><html lang="en">
        <head>
          <meta charset="UTF-8">
          <meta name="viewport" content="width=device-width, initial-scale=1.0">
          <link href="aboutPage.css" rel="stylesheet" type="text/css">
          <title> About Page </title>
        </head>
        <body>
          <header> About Page </header>
          <nav class = "navbar" >
            <div class = "logo" ><a href="/index">Self-Caring Plant</a></div>
                <ul> 
                  <li><a href="/">Home</a></li>
                  <li><a href="/camera">Camera</a></li>
                  <li><a href="/about">About</a></li>
                </ul>
          </nav>
        </body></html>`);
        res.end();//end the response

    } else if (req.url == "/about") {

        res.writeHead(200, { 'Content-Type': 'text/html' });
        res.write(`<html lang="en">
        <head>
          <meta charset="UTF-8">
          <meta name="viewport" content="width=device-width, initial-scale=1.0">
          <link href="aboutPage.css" rel="stylesheet" type="text/css">
          <title> About Page </title>
        </head>
        <body>
          <header> About Page </header>
          <nav class = "navbar" >
            <div class = "logo" ><a href="/index">Self-Caring Plant</a></div>
                <ul> 
                  <li><a href="/">Home</a></li>
                  <li><a href="/camera">Camera</a></li>
                  <li><a href="/about">About</a></li>
                </ul>
          </nav>
          <div class = "content" >
            <div class = "aboutSquare" > 
              <h1> Inspiration </h1>
              <p>
                My friends and I have a lot of plants, 
                but find we never have time to remember to take care of them :(
              </p>
              <h2> What it does </h2>
              <p>
                Automatically adjusts the moisture and infrared radiation levels received by the plant by releasing water from a water tank and activating a light as needed. 
                It outputs the statistical information of the health of the plant onto a website along with a time-lapse video of its growth. Our website also allows you to take a snapshot image for yourself whenever you want. 
                Additionally we apply AI models to classify the plant leaves' nutrient levels and predict whether there are any imbalances or deficiencies. If there are deficiencies, an action will be suggested to the user on the website and a connected LCD screen.
              </p>
              <h3> How we built it </h3>
              <p>
                We used a light sensor to determine the amount of light that the plant is receiving. 
                We used a moisture sensor to determine the moisture level of the soil the plant is in right now (assuming soil-based medium). 
                We used a transistor, resistor, tube, and water pump to control the inflow of water. We used HTML and CSS to build our website that is hosted on Github Pages. 
                We also used a database to store information about the moisture and light sensor and easily transmit information from our board and to our webpage. 
                We used esp-idf, arduino, esp32CAM and esp32s boards to make the systems that monitor the plant.
              </p>
              <h4> Challenges we ran into </h4>
              <p>
                Because we all have different operating systems, 
                finding a database that was compatible for us all was quite difficult. 
                We also ran into a problem of our power supply blowing up and had 
                to figure out alternative methods to powering our system of ESP boards.
              </p>
              <h5> Accomplishments that we're proud of </h5>
              <p>
                Getting consistent hardware measurements. 
              </p>
              <h6> What we learned </h6>
              <p>
                Resolving conflicts.
              </p>
              <h7> What's next for Self Caring Plant </h7>
              <p>
                Expand to care for multiple crops at the same time so that it is available for larger scale plant care precision.
              </p></div></div>
              <script src="website.js"></script></body></html>`);
        res.end(); //end the response
    } else
        res.end('Invalid Request!'); //end the response
  }

    // Server object listens on port 8081
}).listen(3000, () => console.log('Server running on port 3000'));