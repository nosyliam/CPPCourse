#pragma once
#include <cstring>
#include <limits.h>
#include <stdint.h>
#include "bucket.h"

class HashTable {
 public:
  HashTable();
  ~HashTable();

  void add(Student* student);
  bool remove(int id);
  void display();

  void resize(int size);
 private:
  void rehash(Bucket* bucket);
  inline int hash(unsigned id);
  
  int slots = 0;
  Bucket** table = nullptr;
};
