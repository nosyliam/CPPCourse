#include <graph.h>

int Graph::insert(std::string label) {
  // Reconstruct adjacency table
  char** ptr = new char*[++nodes];
  char* pool = new char[nodes * nodes];
  memset(ptr, '\0', sizeof(char*) * nodes);
  // Assign row pointers to their appropriate column pointers
  for (unsigned n = 0; n < nodes; ++n, pool += nodes) {
    memset(pool, '\0', nodes);
    ptr[n] = pool;
    // If old data exists, copy it
    if (adjacency && n < nodes - 1)
      memcpy(pool, adjacency[n], nodes - 1);
  }

  delete [] adjacency;
  
  adjacency = ptr;
  // Map labels to IDs and IDs to labels
  labels[label] = nodes - 1;
  names[nodes - 1] = label;

  maxName = (label.length() > maxName) ? label.length() : maxName;
  return nodes - 1;
}

void Graph::remove(std::string label) {
  // To remove a vertex, we will directly shift the memory of the adjacency table pointer down
  // by a pointer starting at the location of the label. Then, we will shift the memory of each
  // pool down starting at the id of the label. Finally, to correctly match up different ids we will
  // shift the ids of each vector with an id greater than the label down.
  int id = labels[label];
  for (unsigned n = id; n < nodes - 1; ++n)
    adjacency[n] = adjacency[n + 1];

  for (unsigned n = 0; n < nodes; ++n)
    for (unsigned c = id; c < nodes - 1; ++c)
      adjacency[n][c] = adjacency[n][c + 1];

  auto labelsCopy = labels;
  for (auto& vertice : labelsCopy) {
    if (vertice.second > id) {
      labels[vertice.first] = vertice.second - 1;
      names[vertice.second - 1] = vertice.first;
    }
  }

  nodes--;

  
}

bool Graph::connect(std::string start, std::string end, char weight) {
  try {
    adjacency[labels.at(start)][labels.at(end)] = weight;
    return true;
  } catch (...) {
    return false;
  }
}

bool Graph::disconnect(std::string start, std::string end) {
  try {
    adjacency[labels.at(start)][labels.at(end)] = 0;
    return true;
  } catch (...) {
    return false;
  }
}

void Graph::findShortest(std::string start, std::string end) {
  auto cmp = [](std::pair<int, int> left, std::pair<int, int> right) { return (left.first) < (right.second); };
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(cmp)> pq(cmp);
  std::vector<int> dist(nodes, 0xFFFF);
  std::vector<std::vector<int>> path(nodes);

  int src = labels[start], dest = labels[end];
  pq.push(std::make_pair(0, src));
  dist[src] = 0;

  while (!pq.empty()) {
    int node = pq.top().second;
    pq.pop();

    for (int n = 0; n < nodes; n++) {
      if (dist[n] > dist[node] + adjacency[node][n] && adjacency[node][n] != 0) {
	dist[n] = dist[node] + adjacency[node][n];
	// We can record the actual shortest paths by setting the node we're traversings path
	// to the current node with the node appended to the end of it. As each neighbor is traversed, the
	// path list for each node will equal the path required to get to it, resulting in the shortest
	// path to the destination node.
	auto orig = path[node];
	orig.push_back(n);
	path[n] = orig;

	pq.push(std::make_pair(dist[n], n));
      }
    }
  }

  if (dist[dest] == 0xFFFF) {
    std::cout << "No path found";
    return;
  }

  std::cout << "Shortest path: " << names[src];
  for(int n = 0; n < path[dest].size(); ++n)
    std::cout << "->" << names[path[dest][n]];
  
  std::cout << " (distance " << dist[dest] << ")" << std::endl;
}

void Graph::display() {
  // Print top row
  std::cout << std::string(maxName + 1, ' ');
  for (int n = 0; n < nodes; n++)
    std::cout << std::left << std::setw(maxName + 1) << names[n];  

  std::cout << std::endl;
  // Print table
  for (int row = 0; row < nodes; row++) {
    std::cout << std::setw(maxName + 1) << names[row]; 
    for (int col = 0; col < nodes; col++) {
      std::cout << std::setw(maxName + 1) << (int) adjacency[row][col]; 
    }
    std::cout << std::endl;
  }
}

Graph::~Graph() {
  delete [] adjacency;
}
  
