import mongoose from 'mongoose';

const recordSchema = new mongoose.Schema({
  key: String,
  data: Array
});

export const Record = mongoose.models.Record || mongoose.model('Record', recordSchema);
