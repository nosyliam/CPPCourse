#include <memory>
#include "student.h"

class Node {
 public:
  Node(Student* val) : val(val) {};
  ~Node();
  
  Node* getNext();
  Student* getStudent();
  void setNext(Node*);
  void setStudent(Student*);
  
 private:
  Node* next = 0;
  std::unique_ptr<Student> val = nullptr;
};
