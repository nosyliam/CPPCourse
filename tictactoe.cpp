#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <stdio.h>

enum Turn { player, ai, end };   
enum Cell { none, x, o };

class Board {
public:
  Board() {};

  void render() {
    std::cout << "    " << "1"              << "    " << "2"              << "    " << "3"              << std::endl << std::endl
              << "a   " << renderCell(0, 0) << "    " << renderCell(0, 1) << "    " << renderCell(0, 2) << std::endl << std::endl
              << "b   " << renderCell(1, 0) << "    " << renderCell(1, 1) << "    " << renderCell(1, 2) << std::endl << std::endl
              << "c   " << renderCell(2, 0) << "    " << renderCell(2, 1) << "    " << renderCell(2, 2) << std::endl << std::endl;
  }

  char renderCell(int row, int col) {
    switch (data[row][col]) {
    case none:
      return '-';
    case x:
      return 'x';
    case o:
      return 'o';
    }  
  }

  Cell getCell(int n) {
    return data[static_cast <int> (std::floor(n / 3))][n % 3];
  }

  Cell setCell(int n, Cell value) {
    data[static_cast <int> (std::floor(n / 3))][n % 3] = value;
  }

  bool winning(Cell player) {
    return (data[0][0] == player && data[0][1] == player && data[0][2] == player) ||
      (data[1][0] == player && data[1][1] == player && data[1][2] == player) ||
      (data[2][0] == player && data[2][1] == player && data[2][2] == player) ||
      (data[0][0] == player && data[1][0] == player && data[2][0] == player) ||
      (data[0][1] == player && data[1][1] == player && data[2][1] == player) ||
      (data[0][2] == player && data[1][2] == player && data[2][2] == player) ||
      (data[0][0] == player && data[1][1] == player && data[2][2] == player) ||
      (data[0][2] == player && data[1][1] == player && data[2][0] == player);
  }

  void receiveTurn() {
    char val[2];

    std::cin.getline(val, sizeof(turn));
	
	if (strlen(val) != 2)
	  return;
    
    // must be in the format (a-c)(1-3)
    if ((val[0] < 96 && val[0] > 100) || (val[1] < 48 && val[1] > 52))
      return;

    int row = val[0] - 97;
    int col = val[1] - 49;
    if (data[row][col] != none)
      return;

    data[row][col] = x;
    turn = ai;
    std::cout << std::endl;
  }

  bool checkDraw() {
    int n = 0;
    for (; n < 9; n++) {
      if (getCell(n) == none) {
	break;
      }
    }
    
    if (n == 8) {
      // All available spots are taken
      return true;
    } else {
      return false;
    }
  }

  
  // https://github.com/ahmadabdolsaheb/minimaxarticle 
  std::pair<int, int> minimax(Cell playing) {
    if (winning(x)) {
      return std::make_pair(-10, 0);
    } else if (winning(o)) {
      return std::make_pair(10, 0);
    } else {
      if (checkDraw()) {
	return std::make_pair(0, 0);
      }
    }

    std::vector<std::pair<int, int> > moves;
    for (int spot = 0; spot < 9; spot++) {
      if (getCell(spot) != none)
	continue;

      setCell(spot, playing);

      std::pair<int, int> result = minimax((playing == x) ? o : x);
      //std::cout << result.first;
      moves.push_back(std::make_pair(result.first, spot));
      
      setCell(spot, none);
    }

    int bestScore;
    std::pair<int, int> bestMove = std::make_pair(0, 0);
    std::vector<std::pair<int, int> >::iterator it;
    if (playing == o) {
      bestScore = -10000;
      for (std::pair<int, int> move : moves) {
	if (move.first > bestScore) {
	  bestScore = move.first;
	  bestMove = move;
	}
      }
    } else {
      bestScore = 10000;
      for (std::pair<int, int> move : moves) {
	if (move.first < bestScore) {
	  bestScore = move.first;
	  bestMove = move;
	}
      }
    }

    return bestMove;
  }

  void calculateTurn() {
    std::pair<int, int> move = minimax(o);
    setCell(move.second, o);
    render();
    turn = player;
    
    // Output player turn message at the end of every AI turn so
    // the message isn't spammed every player turn failure
    if (!checkDraw() && !winning(x) && !winning(o))
      std::cout << "What spot would you like to take?: ";
  }

  int playAgain() {
    char choice;
    std::cin.get(choice);
		
    if (choice == 'y') {
      turn = player;
      memset(data, 0, sizeof(data));
	  std::cout << std::endl;
	  render();
	  std::cout << "What spot would you like to take?: ";
      return 1;
    } else if (choice == 'n') {
      return 0;
    }

    return 1;
  }
  
  int next() {
    if (turn == end) {
      return playAgain();
    }
    
    if (checkDraw()) {
      std::cout << "The game resulted in a draw! Play again? (y/n): ";
      turn = end;
      return 1;
    }
    
    if (winning(x) || winning(o)) {
      const char* winner = winning(o) ? "AI" : "You";
      std::cout << winner << " won! Play again? (y/n): ";
      turn = end;
      return 1;
    }
    
    switch (turn) {
    case player:
      receiveTurn();
      break;
    case ai:
      calculateTurn();
      break;
    }
    
    return 1;
  }

private:
  Cell data[3][3] = {};
  Turn turn = player;
};

int main() {
  Board* TicTacToe = new Board;
  // start the game by asking the player what spot they want first
  TicTacToe->render();
  std::cout << "What spot would you like to take?: ";
  while (true) {
    if (!TicTacToe->next())
      break;
  }
  return 0;
}    
