// Compile with -std=c++11

#include <iostream>
#include "node.h"

const char* value(bool cond) {
  return (cond ? "TRUE" : "FALSE");
}

int main() {
  // Run test cases

  Student* stud = new Student;
  Student* stud2 = new Student;
  Node* n = new Node(stud);
  n->setNext(n);
  stud->id = 1;
  auto del = [n]() -> int { delete n; return n->getStudent() == nullptr; };
  auto set = [n, stud2]() -> bool { n->setStudent(stud2); return n->getStudent() == stud2; };
  std::cout << "On creation: " << std::endl
	    << "\tValue is equivalent to student passed to constructor: " << value((new Node(stud))->getStudent() == stud) << std::endl
            << "\tNext is nullptr by default: " << value((new Node(stud))->getNext() == nullptr) << std::endl
            << "On setNext: " << std::endl
            << "\tNext is set to given node: " << value(n->getNext() == n) << std::endl
            << "On setStudent: " << std::endl
            << "\tValue is set to given student: " << value(set()) << std::endl
            << "On deletion: " << std::endl
            << "\tStudent is nullptr: " << value(del());

  return 0;
}
 
