#pragma once
#include <room.h>

#define loc game.current_room

class GameState {
 public:
  GameState() {};
  ~GameState() {};

  void AddRoom(Room* room)
  {
    rooms.push_back(room);
  }
  
  void UseItem()
  {
    if (equipped_item != nullptr)
      equipped_item->callback(this);
  }
  
  Item* equipped_item;
  Room* current_room;

  int state = 0;
 private:
  std::vector<Room*> rooms;
};
