require('dotenv').config();
const express = require('express');
const app = express();
const port = process.env.PORT || 8080;

const mysql = require('mysql2');
const connection = mysql.createConnection(process.env.DATABASE_URL);

const fs = require('fs');

connection.connect();
app.use(express.static('public'));

app.get('/', (req, res) => {
  connection.query('SELECT * FROM roster', function (err, rows, fields) {
    if (err) throw err;

    // Prepare the table rows HTML
    let tableRows = '';
    rows.forEach((row) => {
      const rowClass = row.status === 'occupied' ? 'occupied-row' : '';
      tableRows += `<tr class="${rowClass}"><td>${row.machine}</td><td>${row.status}</td><td>${row.time_done}</td></tr>`;
    });

    // Calculate countText and countClass
    let countText = '';
    let countClass = '';
    let availableCount = rows.filter(row => row.status.endsWith('available')).length;
    if (availableCount > 0) {
      countText = `${availableCount} Washer${availableCount > 1 ? 's' : ''} Available`;
    } else {
      const earliestTime = rows.reduce((minTime, row) => {
        return row.time_done < minTime ? row.time_done : minTime;
      }, rows[0].time_done);
      countText = `Earliest Time Available: ${earliestTime}`;
      countClass = 'low-count';
    }

    renderResponse(res, countText, tableRows, countClass);
  });
});

function renderResponse(res, countText, tableRows, countClass) {
  const html = fs.readFileSync('./index.html', 'utf8');
  const modifiedHtml = html
    .replace('{{countText}}', countText)
    .replace('{{tableRows}}', tableRows)
    .replace('{{countClass}}', countClass);
  
  res.send(modifiedHtml);
}

const server = app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`);
});
