import mongoose from 'mongoose';

mongoose.connect("mongodb+srv://zohrasin986:shx2025!@cluster0.hfrqo.mongodb.net/store")
  .then(() => console.log('Connected to MongoDB'))
  .catch((err) => console.error('Connection error:', err));

const { Schema, model } = mongoose;

const recordSchema = new Schema({
  key: String,
  data: Array
});

const records = model('records', recordSchema);

// // Create a test item and insert it into the database
// const testItem = new records({
//   key: "testKey",
//   data: ["item1", "item2", "item3"]
// });

// // Save the test item to the database
// testItem.save()
//   .then((savedItem) => {
//     console.log('Test item inserted:', savedItem);
//   })
//   .catch((err) => {
//     console.error('Error inserting test item:', err);
//   });

// To find all records (this is your original query)
const article = await records.findOne();
article.data = [1, 1, 1];
await article.save();
console.log(article);
mongoose.disconnect();