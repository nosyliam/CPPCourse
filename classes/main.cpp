// Compile with -std=c++11

#include <iostream>
#include <functional>
#include <vector>
#include <cstring>
#include <memory>
#include "media.h"
#include "game.h"
#include "music.h"
#include "movie.h"

// Use a mode enum to combine multiple searching modes
// into as single function.
enum SearchMode { TITLE, YEAR };

// Search returns the number of records found; if the result is 0 the program
// will inform the user.
int search(std::vector<std::shared_ptr<Media>>& objects, SearchMode mode, const char* value) {
  int count = 0;
  if (mode == TITLE) {
    const auto val = static_cast<std::string>(value);
    for (auto med : objects) {
      if (med->Title() == val) {
        med->Display();
	count++;
      }
    };
  } else {
    const auto val = atoi(value);
    for (auto med : objects) {
      if (med->Year() == val) {
	med->Display();
	count++;
      }
    };
  }

  return count;
}

int main() {
  std::vector<std::shared_ptr<Media>> objects;

  std::cout << "Commands: ADD, DELETE (TITLE/YEAR), SEARCH (TITLE/YEAR), QUIT" << std::endl;

  // Mainloop
  while (true) {
    char command[80];
    memset(command, '\0', sizeof(command));

    std::cout << "> ";
    std::cin.getline(command, sizeof(command));

    if (!strncmp(command, "ADD", 3)) {
      // Convert string to media type
      MediaType type = Media::FromString(static_cast<std::string>(command + 4));
      // Create media type and allow it to fill it's fields
      std::shared_ptr<Media> media;
      switch (type) {
      case MediaType::Undefined:
	std::cout << "Invalid media type. Available types are Music, Game, and Movie." << std::endl;
	continue;
      case MediaType::Game:
        media = std::shared_ptr<Media>(new Game);
	break;
      case MediaType::Music:
        media = std::shared_ptr<Media>(new Music);
	break;
      case MediaType::Movie:
        media = std::shared_ptr<Media>(new Movie);
        break;
      }

      media->Fill();
      objects.push_back(media);
    }

    if (!strncmp(command, "LIST", 4)) {
      for (auto media : objects) {
	media->Display();
      }
    }

    if (!strncmp(command, "SEARCH", 6)) {
      int result = 0;
      if (!strncmp(command + 7, "TITLE", 5)) {
	result = search(objects, TITLE, command + 13);	
      } else if (!strncmp(command + 7, "YEAR", 4)) {
	result = search(objects, YEAR, command + 12);
      } else {
	continue;
      }

      if (!result)
	std::cout << "Nothing found.";

      std::cout << std::endl;
    }

    if (!strncmp(command, "DELETE", 6)) {
      int count = 0;
      std::function<bool(const std::shared_ptr<Media> o)> pred;
      // We'll conveniently predefine a predicate for std::remove_if -- it uses
      // a pretty hacky ternary operation to keep everything in a 1-liner while
      // still counting the number of records deleted.

      
      if (!strncmp(command + 7, "TITLE", 5)) {
	const auto val = static_cast<std::string>(command + 13);
	pred = [&] (const std::shared_ptr<Media> o) { return (o->Title() == val) ? (bool) ++count : false; };
	objects.erase(std::remove_if(objects.begin(), objects.end(), pred), objects.end());
      } else if (!strncmp(command + 7, "YEAR", 4)) {
	const auto val = atoi(command + 12);
	pred = [&] (const std::shared_ptr<Media> o) { return (o->Year() == val) ? (bool) ++count : false; };
	objects.erase(std::remove_if(objects.begin(), objects.end(), pred), objects.end());
      } else {
	continue;
      }

      if (!count) {
	std::cout << "Nothing to delete." << std::endl;
      } else {
	std::cout << "Deleted " << count << " records." << std::endl;
      }
    }

    if (!strcmp(command, "QUIT"))
      return 0;
  }
}
