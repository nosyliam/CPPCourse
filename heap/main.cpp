// Compile with -std=c++11
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "heap.hpp"

int main() {
  Heap heap;
  std::string in;
  std::cout << "Enter filename or space-seperated numbers: ";
  std::getline(std::cin, in);

  // Test file first
  std::string strbuf;
  std::ifstream file (in);
  if (file.is_open()) {
    while (std::getline(file, strbuf, ',')) {
      try {
	heap.insert(std::stoi(strbuf));
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
      heap.insert(std::stoi(buf));

  }

  heap.display();
  while (!heap.empty())
    std::cout << heap.extract() << std::endl;
  
  return 0;
}
