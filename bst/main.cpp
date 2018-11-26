#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "tree.hpp"

int main() {
  Tree bst;
  std::string in;
  std::cout << "Enter filename or space-seperated numbers: ";
  std::getline(std::cin, in);

  // Test file first
  std::string strbuf;
  std::ifstream file (in);
  if (file.is_open()) {
    while (std::getline(file, strbuf, ',')) {
      try {
	bst.insert(std::stoi(strbuf));
      } catch (const std::invalid_argument& ia) {
	std::cerr << "Invalid argument: " << ia.what() << std::endl;
	return 0;
      }
    }

    file.close();
  } else {
    // Insert by spaces
    std::string buf;
    std::istringstream input (in, std::istringstream::in);
    while (input >> buf)
      bst.insert(std::stoi(buf));

  }

  bst.display();

  std::cout << "Commands: PRINT, ADD (N >= 0), REMOVE (N >= 0)" << std::endl;
  // Run the command loop
  while (true) {
    char input[80];
    memset(input, '\0', sizeof(input));
    
    std::cin.getline(input, sizeof(input));
    if (strcmp(input, "PRINT") == 0) {
      bst.display();
    }

    if (strncmp(input, "ADD", 3) == 0) {
      int n = atoi(input + 4);
      if (n == 0 && *(input + 4) != '0')
	continue;

      bst.insert(n);
    }

    if (strncmp(input, "REMOVE", 6) == 0) {
      int n = atoi(input + 7);
      if (n == 0 && *(input + 7) != '0')
	continue;

      bst.remove(n);
    }
  }
  
  return 0;
}
