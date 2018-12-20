#pragma once
#include <functional>
#include <iostream>
#include <cmath>
#include <cstring>

enum class Color {
  Red,
  Black
};

class Tree {
  struct Node {
    Node(int value = 0) : value(value) {};
    
    Node* grandparent()
    {
      if (!parent)
	return nullptr;

      return parent->parent;
    };
    
    Node* sibling()
    {
      if (!parent)
	return nullptr;

      return (this == parent->left) ? parent->right : parent->left;
    };
    
    Node* uncle()
    {
      if (!grandparent())
	return nullptr;

      return parent->sibling();
    };

    int depth()
    {
      int n = 1;
      if (left)
	n = 1 + left->depth();

      if (right)
	n = (right->depth() + 1 > n) ? 1 + right->depth() : n;

      return n;
    };
    
    Node* parent = nullptr, *left = nullptr, *right = nullptr;
    Color color = Color::Red;
    int value;
  };
  
public:
  void insert(int n);
  void remove(int n);
  bool search(int n);
  void display() const;
private:
  void rotateRight(Node* n);
  void rotateLeft(Node* n);
  void repaintTree(Node* n);
  void removeOneChild(Node* n);
  Node* find(int n, Node* base);

  Node* root = nullptr;
};
