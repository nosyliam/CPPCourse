
#include <stdio.h>
#include <iostream>
#include <stdlib.h>;

int main() {
  while (true) {
    int input;
    int num;
    int guesses;
    
    srand(time(NULL));
    num = rand() % 100;

    while (input != num) {
      std::cout << "What's your guess?: ";
      std::cin >> input;
      if (input < num)
	std::cout << "Your guess was too low" << std::endl;

      if (num < input)
	std::cout << "Your guess was too high" << std::endl;

    }

    std::cout << "Your guess was correct! The number was " << num << "." << std::endl;

    char choice;
    std::cout << "Play again? (y/n): ";
    while (true) {
      std::cin >> choice;
      if (choice == 'y' || choice == 'n')
	break;
    }

    if (choice == 'y')
      continue;

    if (choice == 'n')
      return 0;
    
  }
  
  return 0;
}
