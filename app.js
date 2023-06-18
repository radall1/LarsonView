require('dotenv').config(); // Load environment variables from .env file

const express = require('express');
const app = express();
const port = process.env.PORT ?? 8010; // Set the port number from environment variables or use 8010 as default

const mysql = require('mysql2');
const dbConnection = mysql.createConnection(process.env.DATABASE_URL); // Create a connection to the MySQL database using the provided URL

const fs = require('fs');

dbConnection.connect(); // Connect to the MySQL database

app.use(express.static('public')); // Serve static files from the 'public' directory

app.get('/', (req, res) => {
  dbConnection.query('SELECT * FROM roster', (error, rows) => { // Execute a SQL query to retrieve data from the 'roster' table
    if (error) throw error; // If there is an error, throw it to be handled by the error handler

    // Prepare the box content HTML
    let boxHtml = '';
    rows.forEach((row) => {
      const boxClass = row.status === 'occupied' ? 'occupied-box' : 'available-box';

      boxHtml += `<div class="box ${boxClass}"><h3>${row.machine}</h3><p>${row.status}</p><p>${row.time_done}</p></div>`;
    });

    // Calculate availability text and class
    let availabilityText = '';
    let availabilityClass = '';
    let availableWashersCount = rows.filter((row) => row.status.endsWith('available')).length;
    if (availableWashersCount > 0) {
      availabilityText = `${availableWashersCount} Washer${availableWashersCount > 1 ? 's' : ''} Available`;
    } else {
      const earliestTime = rows.reduce((minTime, row) => (row.time_done < minTime ? row.time_done : minTime), rows[0].time_done);
      availabilityText = `Earliest Time Available: ${earliestTime}`;
      availabilityClass = 'low-count';
    }

    renderResponse(res, availabilityText, boxHtml, availabilityClass);
  });
});

function renderResponse(res, availabilityText, boxHtml, availabilityClass) {
  const htmlContent = fs.readFileSync('./index.html', 'utf8'); // Read the content of the HTML file
  const modifiedHtml = htmlContent.replace('{{availabilityText}}', availabilityText).replace('{{boxHtml}}', boxHtml).replace('{{availabilityClass}}', availabilityClass);

  res.send(modifiedHtml); // Send the modified HTML as the response
}

const server = app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`); // Start the server and log a message indicating the server is running
});
