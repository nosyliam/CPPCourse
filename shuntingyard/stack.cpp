#include "node.hpp"
#include "stack.hpp"
#include <iostream>

template <typename T>
Stack<T>::Node::~Node() {
  // To pop a node from the stack, we'll simply remove the top and set the node before to top
};

template <typename T>
T Stack<T>::pop() {
  if (!top)
    throw std::out_of_range("stack is empty");

  T val = top->val;
  // Destruct the node and set the top appropriately
  Node* tmp = top->before; 
  delete top;
  top = tmp;

  return val;
};


template <typename T>
T Stack<T>::peek() const {
  if (!top)
    return (T) 0;

  return top->val;
};

template <typename T>
void Stack<T>::push(T val) {
  top = new Node(val, top);
}

template <typename T>
bool Stack<T>::empty() {
  return top == nullptr;
}

template <typename T>
Stack<T>::~Stack() {
  
};

// Explicit template instantiation
template class Stack<char>;
template class Stack<Node*>;
