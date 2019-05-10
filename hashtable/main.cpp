#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <string.h>
#include "table.h"

#define COPY(STR, LEN) (char *) memset((char *) memcpy(new char[LEN + 1], STR, LEN) + LEN, '\0', 1) - LEN

char* paramAt(char* str, int n) {
  for (; n != 0; str++) {
    if (*str == '\0')
      n--;
  }

  return str;
}

void stripSpaces(char* str) {
  for (; *str != '\0'; str++) {
    if (*str == ' ')
      *str = '\0';
  }
}

bool generate(HashTable* table, std::string firstNamesList, std::string lastNamesList, int count) {
  if (!count)
    return false;
  
  std::ifstream firstNamesFile(firstNamesList);
  std::ifstream lastNamesFile(lastNamesList);

  if (!firstNamesFile.is_open() || !lastNamesFile.is_open())
    return false;
  
  std::vector<char*> firstNames, lastNames;

  std::string strbuf;
  while (std::getline(firstNamesFile, strbuf)) {
    firstNames.push_back(COPY(strbuf.c_str(), strbuf.length()));
  }
  while (std::getline(lastNamesFile, strbuf)) {
    lastNames.push_back(COPY(strbuf.c_str(), strbuf.length()));
  }   

  srand(time(NULL));
  for (unsigned n = 0; n < count; n++) 
    table->add(new Student(rand() % 1000000, firstNames.at(rand() % firstNames.size()),
			   lastNames.at(rand() % lastNames.size()), (3) * ((((float) rand()) / (float) RAND_MAX)) + 1));

  std::cout << "Generated " << count << " students." << std::endl;
  return true;
}

int main() {
  HashTable table;

  std::cout << "Commands: ADD, PRINT, DELETE <ID>, QUIT" << std::endl
            << "Student Generator: GENERATE <FIRST NAMES FILE> <LAST NAMES FILE> <COUNT>" << std::endl;

  char command[80];
  while (true) {
    memset(command, '\0', sizeof(command));
    std::cout << "> ";
    std::cin.getline(command, sizeof(command));

    if (!strcmp(command, "ADD")) {
      char buffer[255];
      char* first = new char[255];
      char* last = new char[255];
      double gpa = 0.0;
      int id = 0;

      memset(first, '\0', 255);
      std::cout << "First Name: ";
      std::cin.getline(first, 255);

      memset(last, '\0', 255);
      std::cout << "Last Name: ";
      std::cin.getline(last, 255);
      
      std::cout << "ID: ";
      while (!id) {
	memset(buffer, '\0', 255);
        std::cin.getline(buffer, 255);
	id = atoi(buffer);
	if (!id)
	  std::cout << "The ID you entered was invalid. Please try again: ";
      }

      std::cout << "GPA: ";
      while (gpa == 0.0) {
	memset(buffer, '\0', 255);
	std::cin.getline(buffer, 255);
	gpa = atof(buffer);
	if (gpa == 0.0)
	  std::cout << "The GPA you entered was invalid. Please try again: ";
      }

      table.add(new Student(id, first, last, gpa));
      std::cout << "Student added to list" << std::endl;
    } else if (!strcmp(command, "PRINT")) {
      table.display();
    } else if (!strncmp(command, "DELETE", 6)) {
      int id = atoi(command + 7);
      if (!table.remove(id)) {
	std::cout << "Unable to remove ID " << id << "." << std::endl;
      } else {
	std::cout << "Successfully removed ID " << id << "." << std::endl;
      }
    } else if (!strcmp(command, "QUIT")) {
      break;
    } else if (!strncmp(command, "GENERATE", 8)) {
      stripSpaces(command);
      if (!generate(&table, std::string(paramAt(command, 1)), std::string(paramAt(command, 2)), std::atoi(paramAt(command, 3)))) {
	std::cout << "Invalid file name or student count specified." << std::endl;
      }
    }
    
  }
  return 0;
}
