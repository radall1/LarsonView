require('dotenv').config();
const express = require('express');
const app = express();
const port = process.env.PORT || 49236;

const mysql = require('mysql2');
const connection = mysql.createConnection(process.env.DATABASE_URL);

connection.connect();
app.use(express.static('public'));
//app.use('/favicon.ico', (req, res) => res.status(204));

app.get('/', (req, res) => {
  connection.query('SELECT * FROM roster', function (err, rows, fields) {
    if (err) throw err;

    // Prepare the HTML table structure
    let table = '<table>';
    table += '<tr><th>Machine</th><th>Status</th><th>ETA</th></tr>';

    // Iterate over the rows and populate the table
    let availableCount = 0;
    rows.forEach((row) => {
      const rowClass = row.status === 'occupied' ? 'occupied-row' : '';
      table += `<tr class="${rowClass}"><td>${row.machine}</td><td>${row.status}</td><td>${row.time_done}</td></tr>`;

      if (row.status.endsWith('available')) {
        availableCount++;
      }
    });

    // Check if there are available machines
    let countClass = '';
    if (availableCount > 0) {
      const countText = `${availableCount} Washer${availableCount > 1 ? 's' : ''} Available`;
      renderResponse(countText);
    } else {
      connection.query('SELECT MIN(time_done) AS earliest_time FROM roster', function (err, rowse) {
        if (err) throw err;
        const earliestTime = rowse[0].earliest_time;
        const countText = `Earliest Time Available: ${earliestTime}`;
        renderResponse(countText);
      });
      countClass = 'low-count';
    }

    table += '</table>';

    function renderResponse(countText) {
      res.send(`
        <!DOCTYPE html>
        <html>
          <head>
            <title>LarsonView</title> 
            <link rel="icon" href="favicon.png" type="image/png">  
            <link rel="icon" href="/favicon.ico" type="image/x-icon">
            <link href="https://fonts.googleapis.com/css2?family=Fira+Code:wght@500&display=swap" rel="stylesheet">
            <style>
              body {
                text-align: center;
                font-family: 'Fira Code', monospace;
                background: #2C3A47;
                color: #F8EFBA;
              }

              table {
                margin: 0 auto;
                border-collapse: collapse;
                width: 80%;
                background-color: rgba(88, 177, 159, 0.5);
                padding: 12px;
              }

              th {
                background-color: #222C36;
                color: #F8EFBA;
                padding: 8px;
              }

              td {
                padding: 8px;
              }

              .count-container {
                margin-top: 20px;
                background-color: rgba(88, 177, 159, 0.8);
                padding: 10px;
                display: inline-block;
              }

              .count {
                font-size: 20px;
                color: #F8EFBA;
              }

              .low-count {
                background-color: red;
              }

              .occupied-row {
                background-color: red;
              }
            </style>
            <script>
              // Refresh the page every 10 seconds
              setInterval(() => {
                location.reload();
              }, 10000);
            </script>
          </head>
          <body>
            <h1>LarsonView</h1>
            <div class="count-container ${countClass}">
              <div class="count">
                ${countText}
              </div>
            </div>
            <h2>Machine Roster</h2>
            ${table}
          </body>
        </html>
      `);
    }
  });
});

const server = app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`);
});
