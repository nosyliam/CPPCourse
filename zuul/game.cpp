// Compile with -std=c++11
#include <iostream>
#include <cstring>
#include <algorithm>
#include <game.h>

int main() {
  GameState game;

  // Define room and item medatadata. Item callback functions
  // are defined within the metadata as lambdas.
  ROOM_START(15, "outside", "There's kids playing soccer in the distant fields.");
  ROOM_END(15);

  ROOM_START(14, "the choir room", "You wish you could sit down in one of the many seats.");
  ITEM(14, "CHAIR", [&](GameState* state) {
      if (state->state != 3) {
	std::cout << "The chair feels cold to touch." << std::endl;
	return;
      }

      if (state->current_room->name != "the computer lab") {
	std::cout << "The chair is so comfortable! You'd love to sit down with it on a computer." << std::endl;
      } else {
	std::cout << "You gently set the chair down." << std::endl;
	delete state->equipped_item;
	state->equipped_item = nullptr;
	state->state++;
      }
  });
  ROOM_END(14);
  
  ROOM_START(13, "the band room", "You're not supposed to be in here, but whatever. Trophies and band equipment line the walls.");
  NEIGHBOR(13, WEST, 15);
  NEIGHBOR(15, EAST, 13);
  NEIGHBOR(13, SOUTH, 14);
  NEIGHBOR(14, NORTH, 13);
  ROOM_END(13);
  
  ROOM_START(12, "3 hall", "You can faintly hear music from the dance room.");
  NEIGHBOR(12, WEST, 13);
  NEIGHBOR(13, EAST, 12);
  ROOM_END(12);
  
  ROOM_START(11, "the auditorium", "You can see little. It's fairly dark in here.");
  ROOM_END(11);
  
  ROOM_START(10, "the gym", "You bounce on your step from the recently-renovated gym floor.");
  ROOM_END(10);
  
  ROOM_START(9, "J hall", "It's silent except for the buzzing water fountain.");
  NEIGHBOR(9, WEST, 12);
  NEIGHBOR(12, EAST, 9);
  NEIGHBOR(9, NORTH, 10);
  NEIGHBOR(10, SOUTH, 9);
  ROOM_END(9);
  
  ROOM_START(8, "2 hall", "There doesn't seem to be anything special here.");
  NEIGHBOR(8, WEST, 9);
  NEIGHBOR(9, EAST, 8);
  NEIGHBOR(8, NORTH, 11);
  NEIGHBOR(11, SOUTH, 8);
  ROOM_END(8);
  
  ROOM_START(7, "the cafeteria", "The freshly-mopped linoleum is still squeaky.");
  NEIGHBOR(7, WEST, 8);
  NEIGHBOR(8, EAST, 7);
  ITEM(7, "SPOONS", [&](GameState* state) {
      if (state->state != 0) {
	std::cout << "You have no use for these spoons." << std::endl;
	return;
      }

      if (state->current_room->name != "the computer lab") {
	std::cout << "There's nothing to eat with these spoons.. they could be used in a computer, though." << std::endl;
      } else {
	std::cout << "You prop up the computer screen with the spoons. You can now clearly see the boldly black screen." << std::endl;
	delete state->equipped_item;
	state->equipped_item = nullptr;
	state->state++;
      }
  });
  ROOM_END(7);
  
  ROOM_START(6, "the robotics lab", "Everyone's toying around with their cool robots. You can hear the whirring of motors.");
  ITEM(6, "BUTTONS", [&](GameState* state) {
      if (state->state != 2) {
	std::cout << "You click the button. Nothing happens." << std::endl;
        return;
      }

      if (state->current_room->name != "the computer lab") {
	std::cout << "You inspect the button. It would fit great as a power switch." << std::endl;
      } else {
	std::cout << "You replace the power button on the computer." << std::endl;
        delete state->equipped_item;
        state->equipped_item = nullptr;
	state->state++;
      }
  });
  ROOM_END(6);
  
  ROOM_START(5, "F hall", "There doesn't seem to be anything special here.");
  NEIGHBOR(5, SOUTH, 6);
  NEIGHBOR(6, NORTH, 5);
  ROOM_END(5);
  
  ROOM_START(4, "main hall", "Posters advertising clubs line the wall. You think you should join one.");
  NEIGHBOR(4, SOUTH, 5);
  NEIGHBOR(5, NORTH, 4);
  ROOM_END(4);
  
  ROOM_START(3, "the lower commons", "You can hear the humming of the vending machines.");
  NEIGHBOR(3, WEST, 7);
  NEIGHBOR(7, EAST, 3);
  NEIGHBOR(3, EAST, 4);
  NEIGHBOR(4, WEST, 3);
  ITEM(3, "CABLES", [&](GameState* state) {
      if (state->state != 1) {
	std::cout << "These electrical cables connect the vending machine to power. What use would you have for them?" << std::endl;
	return;
      }

      if (state->current_room->name != "the computer lab") {
	std::cout << "Yanked out of the vending machines, these cabels can connect any device to power. Take them back to the computer lab!" << std::endl;
      } else {
	std::cout << "You connect the cable to an electrical socket and then to the computer... a spark flickers." << std::endl;
	delete state->equipped_item;
	state->equipped_item = nullptr;
	state->state++;
      }
  });    
  ROOM_END(3);
  
  ROOM_START(2, "1 hall", "Silence. Try not to get spotted by the hall monitor.");
  NEIGHBOR(2, NORTH, 3);
  NEIGHBOR(2, EAST, 5);
  NEIGHBOR(5, WEST, 2);
  NEIGHBOR(3, SOUTH, 2);
  ROOM_END(2);

  ROOM_START(1, "the computer lab", "You try to start your computer, but it won't boot up. You've repaired your computer before, but you don't have the right materials to do so. Maybe you can find some materials around the school?");
  ITEM(1, "COMPUTER", [&](GameState* state) {
      switch (state->state) {
      case 0:
	std::cout << "The hinges holding up the screen seem to be broken. Maybe you could use some plastic to hold it up?" << std::endl;
	break;
      case 1:
	std::cout << "The screen is up, but there's no power cable. There's bound to be some in the vending machines." << std::endl;
	break;
      case 2:
	std::cout << "It appears as if the power button is broken. Last you checked, the robotics room was full of them." << std::endl;
	break;
      case 3:
	std::cout << "You'd like to use the computer, but you don't have a chair. There has to be some chairs around the school." << std::endl;
	break;
      case 4:
	std::cout << "You sit down on the chair; time to go back to your favorite C++ programming class. Thanks for playing!" << std::endl;
	exit(0);
	break;
      }
  });
  NEIGHBOR(1, WEST, 2);
  NEIGHBOR(2, EAST, 1);
  ROOM_END(1);

  // Default room is the computer lab
  ROOM_SET(1);

  std::cout << "Commands: WHERE, HANDS, GRAB, USE, DROP, GO, EXIT" << std::endl;
  
  // Gameloop
  while (true) {
    char command[80];

    std::cout << "> ";
    std::cin.getline(command, sizeof(command));
    
    if (!strcmp(command, "WHERE")) {
      std::cout << "You are in " << loc->name << ". ";
      // If there's items, print them out in a nice human-readable format
      if (loc->items.size()) {
	std::cout << "There is a ";
	for (int i = 0; i < loc->items.size(); i++) {
	  std::string& name = loc->items[i]->name;
	  if (!i) {
	    std::cout << name;
	  } else if (i == loc->items.size() - 1) {
	    std::cout << "and a " << name;
	  } else {
	    std::cout << ", a " << name;
	  }
	}
	std::cout << ". ";
      }

      std::cout << loc->state << std::endl;

      if (!loc->neighbors.size()) {
	std::cout << "There are no exits.";
      } else {
	std::cout << "There are exits: " << std::endl;
	// Go through the room's neighbors and print them in a human-readable format
	for (std::map<Direction, Room*>::iterator it = loc->neighbors.begin(); it != loc->neighbors.end(); ++it)
	  std::cout << [=] (Direction dir) {
	    switch (dir) {
	    case Direction::NORTH:
	      return "NORTH";
	    case Direction::EAST:
	      return "EAST";
	    case Direction::SOUTH:
	      return "SOUTH";
	    case Direction::WEST:
	      return "WEST";
	    };
	  }(it->first) << std::endl; 
      }
      
      std::cout << std::endl;
    }

    if (!strncmp(command, "GO", 2)) {
      Direction dir;
      std::string input = static_cast<std::string>(command + 3);
      std::transform(input.begin(), input.end(), input.begin(), ::toupper);
      if (input == "NORTH") {
	dir = Direction::NORTH;
      } else if (input == "EAST") {
	dir = Direction::EAST;
      } else if (input == "SOUTH") {
	dir = Direction::SOUTH;
      } else if (input == "WEST") {
	dir = Direction::WEST;
      } else {
	std::cout << "You can't go that way." << std::endl;
	continue;
      }

      std::map<Direction, Room*>::iterator it = loc->neighbors.find(dir);
      if (it != loc->neighbors.end()) {
	std::cout << "You went " << input << "." << std::endl;
	game.current_room = (*it).second;
      } else {
	std::cout << "You can't go that way." << std::endl;
      }
    }
      
    if (!strncmp(command, "GRAB", 3)) {
      if (game.equipped_item != nullptr) {
	std::cout << "Your hands are already full." << std::endl;
	continue;
      }
      
      std::string name = static_cast<std::string>(command + 5);
      Item* item = loc->FindItem(name);
      if (item != nullptr) {
	std::cout << "You grab the " << item->name << "." << std::endl;
	game.equipped_item = item;
	// Remove the item from the room
	loc->items.erase(std::remove(loc->items.begin(), loc->items.end(), item));
      } else {
	std::cout << "You can't seem to find a " << name << "." << std::endl;
      }
    }

    if (!strcmp(command, "DROP")) {
      if (game.equipped_item != nullptr) {
	std::cout << "You drop the " << game.equipped_item->name << "." << std::endl;
	// Add the item back5B
	loc->AddItem(game.equipped_item);
	game.equipped_item = nullptr;
      } else {
	std::cout << "You don't have anything in your hands." << std::endl;
      }
    }

    if (!strcmp(command, "HANDS")) {
      if (game.equipped_item != nullptr) {
	std::cout << "You are holding a " << game.equipped_item->name << "." << std::endl;
      } else {
	std::cout << "You don't have anything in your hands." << std::endl;
      }
    }

    if (!strncmp(command, "USE", 3)) {
      if (game.equipped_item != nullptr) {
	game.UseItem();
      } else {
	std::cout << "You don't have anything in your hands." << std::endl;
      }
    }

    if (!strcmp(command, "EXIT")) {
      exit(0);
    }
  }

  return 0;
}
