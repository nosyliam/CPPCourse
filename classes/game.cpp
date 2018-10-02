#include <iostream>
#include <cstdlib>
#include <cstring>
#include "game.h"

MediaType Game::Type() {
  return MediaType::Game;
}

void Game::Display() {
  std::cout << Title() << " (" << Year() << ") by " << Publisher() << " rated " << Rating() << std::endl;
}

// Fill publisher and rating
void Game::Fill() {
  this->Media::Fill();

  char buffer[255];
  std::cout << "Publisher: ";
  std::cin.getline(buffer, sizeof(buffer));
  m_publisher = buffer;

  while (!m_rating) {
    memset(buffer, '\0', sizeof(buffer));
    std::cout << "Rating: ";
    std::cin.getline(buffer, sizeof(buffer));
    m_rating = atoi(buffer);
  }
}

std::string Game::Publisher() {
  return m_publisher;
}

int Game::Rating() {
  return m_rating;
}
