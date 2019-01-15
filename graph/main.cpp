#include "graph.h"
#include "vertex.h"
#include <iostream>

int main() {
  Graph graph;
  Vertex vertex1("test", graph);
  //std::cout << "test" << vertex1.id;
  Vertex vertex2("hi", graph);
  graph.adjacency[vertex1.id][vertex2.id] = true;
  std::cout << graph.adjacency[vertex1.id][vertex2.id] << "test" << std::endl;
  Vertex vertex3("lol", graph);
  std::cout << graph.adjacency[vertex1.id][vertex2.id] << "test" << std::endl;
  return 0;
}
