#include "table.h"

HashTable::HashTable() {
  resize(101);
}

void HashTable::add(Student* student) {
  Bucket* bucket = table[hash(student->id)];
  bucket->add(student);
  // If there are more than 3 collisions, double the size of the table.
  if (bucket->size >= 3)
    resize(slots * 2);
}

bool HashTable::remove(int id) {
  Bucket* bucket = table[hash(id)];

  // The bucket will attempt to remove the given id; if it does not succed, it will return false.
  return (bool) bucket->removeById(id);
}

void HashTable::display() {
  for (int n = 0; n < slots; n++) {
    table[n]->display();
  }
}

void HashTable::rehash(Bucket* bucket) {
  if (bucket->head) {
    Entry* head = bucket->head;
    int size = bucket->size;
    
    int entryHash;
    for (int n = 0; n < bucket->size; n++) {
      entryHash = hash(bucket->at(n)->id);
      if (bucket->location != entryHash) {
	// The entry in this bucket doesn't belong here; we need to move it over.
        table[entryHash]->add(bucket->at(n));
	bucket->remove(n);
	n--;
      }
    }
  }
}

void HashTable::resize(int size) {
  Bucket** ptr = new Bucket*[size];
  // Allocate new buckets
  for (unsigned n = slots; n < size; n++)
    ptr[n] = new Bucket(n);

  if (slots) // Copy pointers to old buckets
    memcpy(ptr, table, sizeof(Bucket*) * slots);

  delete [] table;
  table = ptr;
  int oldSize = slots;
  slots = size;
  
  // Rehash the bucket contents
  for (unsigned n = 0; n < oldSize; n++)
    rehash(ptr[n]);
}

static inline uint32_t rotl32 (uint32_t n, unsigned int c)
{
  const unsigned int mask = (CHAR_BIT*sizeof(n) - 1);
  
  c &= mask;
  return (n<<c) | (n>>( (-c)&mask ));
}

inline int HashTable::hash(unsigned id) {
  // FNV hash
  int hash = 2166136261;
  for (unsigned n = 0; n < 24; n += 3) {
    hash = (hash * 16777619) ^ ((id >> n));
  }

  int finalHash = rotl32(hash, (slots + 1) % 23);
  
  return (unsigned int) finalHash % slots;
}

HashTable::~HashTable() {
  for (unsigned n = 0; n < slots; n++)
    delete table[n];
  
  delete [] table;
}
