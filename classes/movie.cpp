#include <iostream>
#include <cstdlib>
#include <cstring>
#include <movie.h>

MediaType Movie::Type() {
  return MediaType::Movie;
}

void Movie::Display() {
  std::cout << Title() << " (" << Duration() << "m, " << Year() << ") directed by " << Director() << " rated " << Rating() << std::endl; 
}

// Fill director, duration, and rating
void Movie::Fill() {
  this->Media::Fill();

  char buffer[255];
  std::cout << "Director: ";
  std::cin.getline(buffer, sizeof(buffer));
  m_director = buffer;

  while (!m_duration) {
    memset(buffer, '\0', sizeof(buffer));
    std::cout << "Duration: ";
    std::cin.getline(buffer, sizeof(buffer));
    m_duration = atoi(buffer);
  }
  
  while (!m_rating) {
    memset(buffer, '\0', sizeof(buffer));
    std::cout << "Rating: ";
    std::cin.getline(buffer, sizeof(buffer));
    m_rating = atoi(buffer);
  }
}

std::string Movie::Director() {
  return m_director;
}

int Movie::Duration() {
  return m_duration;
}

int Movie::Rating() {
  return m_rating;
}
