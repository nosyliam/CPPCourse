#include "graph.h"
#include <iostream>

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

int main() {
  Graph graph;

  std::cout << "Commands: PRINT, ADD VECTOR <label>, REMOVE VECTOR <label>, ADD EDGE <start> <end> <weight>, REMOVE EDGE <start> <end>, SHORTEST <start> <end>" << std::endl;
  // Run the command loop
  while (true) {
    char input[80];
    memset(input, '\0', sizeof(input));

    std::cin.getline(input, sizeof(input));
    if (strcmp(input, "PRINT") == 0) {
      graph.display();
    }

    if (strncmp(input, "ADD VECTOR", 10) == 0) {
      stripSpaces(input);
      char* name = paramAt(input, 2);
      if (*name == '\0')
	continue;

      graph.insert(std::string(name));
    }

    if (strncmp(input, "ADD EDGE", 8) == 0) {
      stripSpaces(input);
      char* start = paramAt(input, 2), *end = paramAt(input, 3), *weight = paramAt(input, 4);
      if (*start == '\0' || *end == '\0' || *weight == '\0')
	continue;

      int n = atoi(weight);
      if (!n) {
	std::cout << "Invalid weight." << std::endl;
	continue;
      }

      if (!graph.connect(std::string(start), std::string(end), (char) n))
	std::cout << "Unable to create edge." << std::endl;
    }

    if (strncmp(input, "REMOVE EDGE", 11) == 0) {
      stripSpaces(input);
      char* start = paramAt(input, 2), *end = paramAt(input, 3);
      if (*start == '\0' || *end == '\0')
	continue;

      if (!graph.disconnect(std::string(start), std::string(end)))
	std::cout << "Unable to remove edge." << std::endl;
    }

    if (strncmp(input, "SHORTEST", 8) == 0) {
      stripSpaces(input);
      char* start = paramAt(input, 1), *end = paramAt(input, 2);
      if (*start == '\0' || *end == '\0')
	continue;

      graph.findShortest(std::string(start), std::string(end));
    }
  }
  return 0;
}
