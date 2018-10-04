#pragma once
#include <string>
#include <algorithm>
#include <cstdlib>

enum class MediaType {
  Undefined,
  Music,
  Game,
  Movie  
};

class Media {
 public:
  explicit Media() {};
  
  virtual MediaType Type()
  {
    return MediaType::Undefined;
  };

  virtual void Display() {};

  // Filler for base fields
  virtual void Fill() {
    char buffer[255];
    
    std::cout << "Title: ";
    std::cin.getline(buffer, sizeof(buffer));
    m_title = buffer;

    // Repeat until valid integer is specified for year
    while (!m_year) {
      memset(buffer, '\0', sizeof(buffer));
      std::cout << "Year: ";
      std::cin.getline(buffer, sizeof(buffer));
      m_year = atoi(buffer);
    }
  };

  std::string Title() const
  {
    return m_title;
  }

  int Year() const
  {
    return m_year;
  }

  static MediaType FromString(std::string str)
  {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    if (str == "game") {
      return MediaType::Game;
    } else if (str == "movie") {
      return MediaType::Movie;
    } else if (str == "music") {
      return MediaType::Music;
    } else {
      return MediaType::Undefined;
    }
  };
  
  
 private:
  std::string m_title = "";
  int m_year = 0;
};
