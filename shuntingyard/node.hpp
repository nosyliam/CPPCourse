#pragma once

class Node {
public:
  Node(char* value) : value(value) {};
  ~Node();
 
  const char* Value() const;
  Node* Left() const;
  Node* Right() const;
  
  void setLeft(Node* value);
  void setRight(Node* value);

  
private:
  const char* value;
  
  Node* left = 0;
  Node* right = 0;
};
