#pragma once
#include <unordered_map>
#include <cstring>

class Graph {
 public:
  Graph() {};
  ~Graph() {};

  int insert(std::string label) {
    // Reconstruct adjacency table
    bool** ptr = new bool*[++nodes];
    bool* pool = new bool[nodes * nodes];
    // Assign row pointers to their appropriate column pointers
    for (unsigned n = 0; n < nodes; ++n, pool += nodes) {
      ptr[n] = pool;
      // If old data exists, copy it
      if (adjacency && n >= nodes)
      	memcpy(pool, adjacency[n], nodes - 1);
    }

    adjacency = ptr;
    labels[label] = nodes;
    return nodes;
  }
  bool** adjacency = nullptr;
 private:
  //bool** adjacency = nullptr;
  std::unordered_map<std::string, int> labels;
  int nodes = 0;
};
