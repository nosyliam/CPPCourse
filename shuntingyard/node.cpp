#include "node.hpp"

const char* Node::Value() const {
  return value;
};

Node* Node::Left() const {
  return left;
};

Node* Node::Right() const {
  return right;
};

void Node::setLeft(Node* value) {
  left = value;
};

void Node::setRight(Node* value) {
  right = value;
};
