#pragma once
#include <functional>
#include <iostream>
#include <cmath>
#include <cstring>

class Tree {
  struct Node {
    Node(int val, Node* parent) : val(val), key(val), parent(parent) {};
    ~Node();

    int depth();
    
    int key; // Priority
    int val; // Value
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent;
  };

public:
  void insert(int val);
  void remove(int val);
  void display() const;

private:
  Node* root = new Node(0, nullptr);
};
