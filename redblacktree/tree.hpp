#pragma once
#include <functional>
#include <iostream>
#include <cmath>
#include <cstring>

#define LEAF Tree::Node::sentinel

enum class Color {
  Red,
  Black
};

class Tree {
public:
  struct Node {
    Node(int value = 0) : value(value), left(Node::sentinel), right(Node::sentinel) {};
    static Node * sentinel;
    
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

      Node::sentinel->left = Node::sentinel;
      Node::sentinel->right = Node::sentinel;
      return (this == parent->right) ? parent->left : parent->right;
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
      if (left != Node::sentinel)
	n = 1 + left->depth();

      if (right != Node::sentinel)
	n = (right->depth() + 1 > n) ? 1 + right->depth() : n;

      return n;
    };

    Node *operator->()
    {
      std::cout << "ACCESS" << std::endl;
      if (this == LEAF) {
	LEAF->color = Color::Black;
      }

      return nullptr;
    }
    
    Node* parent = nullptr, *left = Node::sentinel, *right = Node::sentinel;
    Color color = Color::Black;
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
