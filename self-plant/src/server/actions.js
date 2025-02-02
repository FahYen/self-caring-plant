"use server"

import { connectToDatabase } from '@/lib/mongodb';
import { Record } from '@/models/Record';

export async function getRecords() {
  try {
    await connectToDatabase();
    const records = await Record.find({});
    console.log("Retrieved records:", records);
    return { records };
  } catch (error) {
    console.error('Failed to fetch records:', error);
    throw new Error('Failed to fetch records');
  }
}