#pragma once
#include <unordered_map>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include <queue>

class Graph {
 public:
  Graph() {};
  ~Graph();

  int insert(std::string label);
  void remove(std::string label);
  bool connect(std::string start, std::string end, char weight);
  bool disconnect(std::string start, std::string end);
  void findShortest(std::string start, std::string end);
  void display();
  
 private:
  char** adjacency = nullptr;
  std::unordered_map<std::string, int> labels;
  std::unordered_map<int, std::string> names;
  int nodes = 0, maxName = 3;
};
