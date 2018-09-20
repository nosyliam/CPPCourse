#pragma once
#include <vector>
#include <string>
#include <map>
#include <functional>

// Preprocessors for medatadata definition
#define ROOM_START(ID, NAME, STATE) Room* ROOM##ID = new Room(NAME, STATE)
#define NEIGHBOR(ID, DIR, OTHER) ROOM##ID->SetNeighbor(Direction::DIR, ROOM##OTHER)
#define ITEM(ID, NAME, CALLBACK) ROOM##ID->AddItem(new Item(NAME, CALLBACK))
#define ROOM_END(ID) game.AddRoom(ROOM##ID)
#define ROOM_SET(ID) game.current_room = ROOM##ID

class GameState;

// Items are simples structures that use a callback to make modifications to the
// gamestate when used. The callback is expected to sanity check itself upon
// reaching different checkpoints.
struct Item { 
  std::string name;
  const std::function<void(GameState*)>& callback;
  
  Item(std::string name, const std::function<void(GameState*)>& callback) : name(name), callback(callback) {};
};

enum class Direction {
  NORTH,
  EAST,
  SOUTH,
  WEST
};
  

class Room {
 public:
  Room(std::string name, std::string state) : name(name), state(state) {};
  ~Room() {};

  // Metadata utility functions
  Room* At(Direction dir)
  {
    return neighbors.at(dir);
  };

  void SetNeighbor(Direction dir, Room* room)
  {
    neighbors[dir] = room;
  };

  void AddItem(Item* item)
  {
    items.push_back(item);
  };

  void SetState(std::string state)
  {
    state = state; 
  }

  Item* FindItem(std::string name)
  {
    std::vector<Item*>::iterator it = std::find_if(items.begin(), items.end(), [name](const Item* o) { return o->name == name; });
    return (it == items.end()) ? nullptr : *it;
    
  };

  std::string name;
  std::map<Direction, Room*> neighbors;
  std::vector<Item*> items;

  // When an item is used, it is free to modify the gamestate to
  // change a current room's state. This state is displayed when
  // the user requests their current surroundings.
  std::string state;
};
