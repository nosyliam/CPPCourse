// Compile with -std=c++11
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "tree.hpp"

Tree::Node* Tree::Node::sentinel = new Tree::Node();

int main() {
  Tree::Node::sentinel->left = Tree::Node::sentinel;
  Tree::Node::sentinel->right = Tree::Node::sentinel;
  
  Tree rbtree;
  std::string in;
  std::cout << "Enter filename or space-seperated numbers: ";
  std::getline(std::cin, in);

  // Test file first
  std::string strbuf;
  std::ifstream file (in);
  if (file.is_open()) {
    while (std::getline(file, strbuf, ',')) {
      try {
	rbtree.insert(std::stoi(strbuf));
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
      rbtree.insert(std::stoi(buf));

  }

  rbtree.display();

  std::cout << "Commands: PRINT, ADD (N >= 0), REMOVE (N >= 0), SEARCH (N >= 0)" << std::endl;
  // Run the command loop
  while (true) {
    char input[80];
    memset(input, '\0', sizeof(input));

    std::cin.getline(input, sizeof(input));
    if (strcmp(input, "PRINT") == 0) {
      rbtree.display();
    }

    if (strncmp(input, "ADD", 3) == 0) {
      int n = atoi(input + 4);
      if (n == 0 && *(input + 4) != '0')
	continue;

      rbtree.insert(n);
    }

    if (strncmp(input, "REMOVE", 6) == 0) {
      int n = atoi(input + 7);
      if (n == 0 && *(input + 7) != '0')
	continue;

      rbtree.remove(n);
    }

    if (strncmp(input, "SEARCH", 6) == 0) {
      int n = atoi(input + 7);
      if (n == 0 && *(input + 7) != '0')
	continue;

      const char* result = rbtree.search(n) ? "PRESENT" : "NOT PRESENT";
      std::cout << n << " is " << result << std::endl;
    }
  }

  return 0;
}
