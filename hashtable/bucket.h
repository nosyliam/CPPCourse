#pragma once
#include "table.h"
#include <iostream>
#include <iomanip>

struct Student {
  Student(int id, char* firstName, char* lastName, double gpa) : id(id), firstName(firstName), lastName(lastName), gpa(gpa) {};
  char* firstName;
  char* lastName;
  int id;
  double gpa;
};


struct Entry {
  Entry(int id, Student* val) : id(id), ptr(val) {};
  ~Entry() {
    delete ptr;
  };
  int id;
  Student* ptr;
  Entry* next = nullptr;
};

struct Bucket {
  void add(Student* student)
  {
    size++;
    if (!head) {
      head = new Entry(student->id, student);
      return;
    }

    Entry* cursor = head;
    for (; cursor->next; cursor = cursor->next) {};
    cursor->next = new Entry(student->id, student);
  }

  Student* at(int pos)
  {
    if (pos == 0)
      return head->ptr;
    
    Entry* cursor = head;
    for (; pos && cursor->next; pos--) { cursor = cursor->next; }
    return cursor->ptr;
  }

  void remove(int pos)
  {
    size--;
    if (pos == 0) {
      head = (size == 0) ? nullptr : head->next;
      return;
    }

    pos--;
    Entry* prev = head;
    for (; pos && prev->next; pos--) { prev = prev->next; }
    prev->next = prev->next->next;
  }

  bool removeById(int id)
  {
    if (!head)
      return false;
    
    if (id == head->id) {
      Entry* oldHead = head;
      head = (size == 0) ? nullptr : head->next;
      delete oldHead;
      size--;
      return true;
    }

    Entry* prev = head;
    for (; (prev->next) && prev->next->id != id; ) { prev = prev->next; }
    if ((!prev->next) || prev->next->id != id)
      return false;
    
    Entry* toDelete = prev->next;
    prev->next = toDelete->next;
    size--;
    delete toDelete;
    return true;
  }

  void display() {
    if (!head)
      return;

    for (Entry* cursor = head; cursor != nullptr; cursor = cursor->next) {
      std::cout << "[" << location << "] (" << cursor->ptr->id << ") "
	        << cursor->ptr->firstName << " " << cursor->ptr->lastName << ", "
	        << std::fixed << std::setprecision(2) << cursor->ptr->gpa << " GPA" << std::endl;
    }
  }

  Bucket(int location) : location(location) {};
  ~Bucket() {};
  
  Entry* head = nullptr;
  int size = 0;
  int location;
};
