#include <iostream>
#include <cstdlib>
#include <cstring>
#include "music.h"

MediaType Music::Type() {
  return MediaType::Music;
}

void Music::Display() {
  std::cout << Title() << " (" << Duration() << "m, " << Year() << ") by " << Artist() << " and published by " << Publisher() << std::endl;
}

// Fill publisher, artist, and duration
void Music::Fill() {
  this->Media::Fill();

  char buffer[255];
  std::cout << "Publisher: ";
  std::cin.getline(buffer, sizeof(buffer));
  m_publisher = buffer;

  std::cout << "Artist: ";
  std::cin.getline(buffer, sizeof(buffer));
  m_artist = buffer;
  
  while (!m_duration) {
    memset(buffer, '\0', sizeof(buffer));
    std::cout << "Duration: ";
    std::cin.getline(buffer, sizeof(buffer));
    m_duration = atoi(buffer);
  }
}

std::string Music::Publisher() {
  return m_publisher;
}

std::string Music::Artist() {
  return m_artist;
}

int Music::Duration() {
  return m_duration;
}
