#pragma once
#include <iostream>
#include <cmath>
#include <functional>

class Heap {
  class Node {
  public:
    Node(int val, int index = 0, Node* before = nullptr) : val(val), index(index), before(before) {
      if (before)
	before->next = this;
    };

    ~Node();
    Node* up(int n);
    int parent();
    
    int val = 0;
    int index = 0;
    Node* before = nullptr;
    Node* next = nullptr;
  };
public:
  Heap() {};
  ~Heap();

  bool empty() const;
  void display() const;
  void insert(int val);
  int extract();

private:
  Node* head = nullptr;
  Node* tail = nullptr;
  int index = 0;
};
