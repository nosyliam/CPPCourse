#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <math.h>

struct Student {
  char* firstName;
  char* lastName;
  int id;
  double gpa;
};

void add(std::vector<Student*> &students) {
  Student* student = new Student;
  char buffer[255];
  char* first = new char[255];
  char* last = new char[255];

  std::cout << "First Name: ";
  std::cin >> first;
  student->firstName = first;

  std::cout << "Last Name: ";
  std::cin >> last;
  student->lastName = last;

  std::cout << "ID: ";
  while (!student->id) {
    std::cin.getline(buffer, sizeof(buffer));
    student->id = atoi(buffer);
  }

  memset(buffer, 0, sizeof(buffer));
  std::cout << "GPA: ";
  while (!student->gpa) {
    std::cin.getline(buffer, sizeof(buffer));
    student->gpa = atof(buffer);
  }

  students.push_back(student);
  std::cout << "Student added to list" << std::endl;
}

void print(std::vector<Student*> &students) {
  for (Student* student : students) {
    std::cout << student->firstName << " " << student->lastName << ", " << student->id << ", " << std::fixed << std::showpoint << std::setprecision(2) << student->gpa << std::endl;
  }
}

void remove(std::vector<Student*> &students, int id) {
  students.erase(std::remove_if(students.begin(), students.end(), [id](const Student* o) {
	if (o->id == id) { std::cout << "Student deleted" << std::endl; return true; }; }), students.end());
}

int main() {
  std::vector<Student*> students;
  std::cout << "Commands: ADD, PRINT, DELETE" << std::endl;
  while (true) {
    char command[80];
    std::cout << "> ";
    std::cin.getline(command, sizeof(command));
    
    if (!strcmp(command, "ADD")) {
      add(students);	   
    } else if (!strcmp(command, "PRINT")) {
      print(students);
    } else if (!strncmp(command, "DELETE", 6)) {
      int id = atoi(command + 7);
      remove(students, id); 
    }
  }
}
