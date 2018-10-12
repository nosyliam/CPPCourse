#pragma once
#include <stdexcept>

template <typename T>
class Stack {
  class Node {
  public:
    Node(T val, Node* before = nullptr) : val(val), before(before) {};
    ~Node();

    Node* before;
    T val;
  };
public:

  Stack() = default;
  ~Stack();

  T pop();
  T peek() const;
  void push(T val);
  bool empty();
  
private:
  Node* top = 0;
};
