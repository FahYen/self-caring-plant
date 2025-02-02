import mongoose, { mongo } from 'mongoose';

const { Schema, model } = mongoose;

const recordSchema = new Schema({
  key: String,
  data: Array
});

const records = model('records', recordSchema);

async function updateMoisture(models, idx, val) {
  mongoose.connect("mongodb+srv://zohrasin986:shx2025!@cluster0.hfrqo.mongodb.net/store")
  .then(() => console.log('Connected to MongoDB'))
  .catch((err) => console.error('Connection error:', err));
  const article = await records.findOne({"key": "m"});
  article.data[idx] = val;
  await article.save();
  console.log(article);
  mongoose.disconnect();
}

async function resetMoisture(models) {
  const article = await records.findOne({"key": "m"});
  article.data = [0, 0, 0, 0, 0, 0];
  await article.save();
  console.log(article);
}

async function resetLight(models) {
  mongoose.connect("mongodb+srv://zohrasin986:shx2025!@cluster0.hfrqo.mongodb.net/store")
  .then(() => console.log('Connected to MongoDB'))
  .catch((err) => console.error('Connection error:', err));
  const article = await records.findOne({"key": "l"});
  article.data = [0, 0, 0, 0, 0, 0];
  await article.save();
  console.log(article);
}

async function updateLight(models, idx, val) {
  mongoose.connect("mongodb+srv://zohrasin986:shx2025!@cluster0.hfrqo.mongodb.net/store")
  .then(() => console.log('Connected to MongoDB'))
  .catch((err) => console.error('Connection error:', err));
  const article = await records.findOne({"key": "l"});
  article.data[idx] = val;
  await article.save();
  console.log(article);
  mongoose.disconnect();
}

resetLight(records);
resetMoisture(records);
updateMoisture(records, 2, 23);
