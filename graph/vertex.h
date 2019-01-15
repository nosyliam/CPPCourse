#pragma once
#include <string>
#include <graph.h>

struct Vertex {
  Vertex(std::string label, Graph& graph) : graph(graph), id(graph.insert(label)) {};
  ~Vertex()
  {
    //graph.remove(id);
  };

  int id;
  std::string label;
  Graph& graph;
};
