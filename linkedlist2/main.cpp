#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include "Student.h"
#include "Node.h"

void add(Node*& head) {
  Student* student = new Student;
  char buffer[255];
  char* first = new char[255];
  char* last = new char[255];
  student->id = 0;
  student->gpa = 0.0;
  
  // Input student data into structure
  std::cout << "First Name: ";
  std::cin >> first;
  student->firstName = first;

  std::cout << "Last Name: ";
  std::cin >> last;
  student->lastName = last;

  memset(buffer, 0, 255);
  std::cout << "ID: ";
  while (!student->id) {
    std::cin.getline(buffer, sizeof(buffer));
    student->id = atoi(buffer);
  }

  memset(buffer, '\0', sizeof(buffer));
  std::cout << "GPA: ";
  while (!student->gpa) {
    std::cin.getline(buffer, sizeof(buffer));
    student->gpa = atof(buffer);
  }

  // Instantiate the actual node
  Node* node = new Node;
  node->setStudent(student);
   
  if (!head) {
    head = node;
  } else {
    // If the given id is smaller than the head's id, we do not need to recurse the entire list.
    if (head->getStudent()->id > student->id) {
      node->setNext(head);
      head = node;
      return;
    }
    
    // Recurse over the list until the end or until a node
    // has a next node whose id is larger than the given id.
    Node* cursor = head;
    for (; (cursor->getNode()) && cursor->getNode()->getStudent()->id < student->id; cursor = cursor->getNode()) {};

    // cursor->getNode() will either point to the next node or nullptr; either case is fitting
    node->setNext(cursor->getNode());
    cursor->setNext(node);
  }
}

void remove(Node*& head, int id) {
  if (!head) {
    std::cout << "Student list is empty." << std::endl;
    return;
  }

  if (head->getStudent()->id == id) {
    // Student at the front of the list matches
    Node* newHead = head->getNode();
    delete head->getStudent();
    delete head;
    head = newHead;
    return;
  }
  
  // Find the node previous to the node with the given id
  Node* cursor = head;
  for (; (cursor->getNode()) && cursor->getNode()->getStudent()->id != id; cursor = cursor->getNode()) {};

  if (!cursor->getNode()) {
    // We reached the end of the list, but didn't find anything.
    std::cout << "Student with ID not found." << std::endl;
  } else {
    // Delete node and fix links
    Node* newNext = cursor->getNode()->getNode();
    delete cursor->getNode()->getStudent();
    delete cursor->getNode();
    cursor->setNext(newNext);
  }
}

void average(Node*& head) {
  double total;
  int count;
  for (Node* cursor = head; cursor; cursor = cursor->getNode()) {
    count++;
    total += cursor->getStudent()->gpa;
  }

  std::cout << "Average GPA: " << std::fixed << std::showpoint << std::setprecision(2) << total / count << std::endl;
}

void print(Node*& head) {
  if (!head)
    return;

  Student* student;
  for (Node* cursor = head; cursor; cursor = cursor->getNode()) {
    student = cursor->getStudent();
    std::cout << student->firstName << " " <<
                 student->lastName << ", " <<
                 student->id << ", " << std::fixed << std::showpoint << std::setprecision(2) <<
                 student->gpa << std::endl;
  }
}

int main() {
  Node* head;
  std::cout << "Commands: ADD, PRINT, DELETE, AVERAGE, QUIT" << std::endl;
  while (true) {
    char command[80];
    memset(command, '\0', sizeof(command));
    std::cout << "> ";
    std::cin.getline(command, sizeof(command));

    if (!strcmp(command, "ADD")) {
      add(head);
    } else if (!strcmp(command, "PRINT")) {
      print(head);
    } else if (!strncmp(command, "DELETE", 6)) {
      int id = atoi(command + 7);
      remove(head, id);
    } else if (!strcmp(command, "AVERAGE")) {
      average(head);
    } else if (!strcmp(command, "QUIT")) {
      return 0;
    }
  }
}
