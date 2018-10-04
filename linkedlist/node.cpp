#include "node.h"

Node* Node::getNext() {
  return next;
};

void Node::setNext(Node* n) {
  next = n;
}

void Node::setStudent(Student* s) {
  val.reset(s);
}

Student* Node::getStudent() {
  return val.get();
}

Node::~Node() {
  
}
