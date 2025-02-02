const mongoose = require('mongoose');
const express = require('express');
const app = express();
const port = 3000;

app.use(express.static('public'));

mongoose.connect("mongodb+srv://zohrasin986:shx2025!@cluster0.hfrqo.mongodb.net/store")
  .then(() => console.log('Connected to MongoDB'))
  .catch((err) => console.error('Connection error:', err));

const { Schema, model } = mongoose;

const recordSchema = new Schema({
  key: String,
  data: Array
});

const records = model('records', recordSchema);

console.log("records yo ", records);

// async function fetchData() {
//     try {
//       const response = await fetch('/api/items');
//       const data = await response.json();
  
//       // Loop through the first 6 items and update corresponding elements
//       for (let i = 0; i < 6; i++) {
//         const element = document.getElementById(`item-${i}`);
//         if (data[i]) {
//           element.textContent = `${data[i].name}: ${data[i].value}`;
//         } else {
//           element.textContent = 'No data available';
//         }
//       }
//     } catch (error) {
//       console.error('Error fetching data:', error);
//     }
//   }
  
  // Periodically fetch data every 5 seconds
//   setInterval(fetchData, 5000);
  
  // Initial fetch when the page loads
//   fetchData();

 