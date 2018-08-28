#include <iostream>
#include <cstring>
#include <stdbool.h>
#include <stdio.h>

char* strip(char* input) {
  char* stripped = new char[80];
  int pos;
  
  for (; *input != '\0'; input++) {
    if ((*input > 31 && *input < 48) || (*input > 57 && *input < 65))
      continue;

    stripped[pos++] = tolower(*input);
  }
  
  return stripped;
}

bool check(char* input) {
  int len = strlen(input) - 1;
  for (int pos = 0; pos < len; pos++) {
    if (input[pos] != input[len - pos])
      return false;
    
  }
  
  return true;
}

int main() {
  while (true) {
    char input[80];
    std::cout << "Enter a string: ";
    std::cin.getline(input, sizeof(input));
    char* stripped = strip(input);
    bool result = check(stripped);
    if (result)
      std::cout << "Palindrome." << std::endl;
    else
      std::cout << "Not a palindrome." << std::endl;

    delete stripped;
  }
  return 0;
}
