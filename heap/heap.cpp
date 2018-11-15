#include "heap.hpp"

Heap::Node* Heap::Node::up(int n) {
  return (n == 0) ? this : (next != nullptr) ? next->up(--n) : nullptr;
}

// Return the parent index of the node
int Heap::Node::parent() {
  return (index > 1) ? static_cast <int> (std::floor((index - 1) / 2)) : 0;
}

Heap::Node::~Node() {
  
}

Heap::~Heap() {
}

void Heap::insert(int val) {
  if (head == nullptr && tail == nullptr) {
    head = new Node(val, index++);
    tail = head;
    return;
  }

  // Add node to the end of the array; the last node is always the most bottom level.
  tail = new Node(val, index++, tail);

  // Swap child and parent values until the child value is less than the parent value.
  Node* parent = head->up(tail->parent());
  Node* child = tail;
  while (parent->val < val) {
    child->val = parent->val;
    parent->val = val;
    child = parent;
    if (parent == head)
      break;
    
    parent = head->up(parent->parent());
  }
}

int Heap::extract() {
  if (head == tail) {
    // Clean up the list if we're removing extracting the final value.
    int tmp = head->val;
    delete head;
    head = nullptr;
    tail = nullptr;
    return tmp;
  }

  
  // Pop the root of the heap
  int val = head->val;
  Node* before = tail->before;
  tail->index = 0;
  tail->next = head->next;
  tail->before = nullptr;
  delete head;
  head = tail;
  tail = before;
  tail->next = nullptr;
  index--;

  // Use max-heapify to sort the heap correctly
  Node* largest = head;
  Node* root = head;
  auto sort = [&] () mutable {
    Node* tmp = nullptr;
    int left = (largest->index * 2) + 1;
    int right = (largest->index * 2) + 2;

    if (left < index) {
      tmp = head->up(left);
      largest = (tmp->val > largest->val) ? tmp : largest;
    }

    if (right < index) {
      tmp = head->up(right);
      largest = (tmp->val > largest->val) ? tmp : largest;
    }
  };

  sort();
  // If the tree or subtree's children are larger than the parent, then
  // it's values are swapped and sorted recursively. As a result, every tree
  // in the heap will follow the heap property.
  while (largest != root) {
    std::swap(largest->val, root->val);
    root = largest;
    sort();
  }

  return val;
}

bool Heap::empty() const {
  return index == 0;
}

void Heap::display() const {
  if (index == 0) return;

  // To calculate the number of spaces needed between nodes to pleasently display the tree, a recursive
  // function (in this case in the form of a lambda) is required. Between each level, 8 more spaces are
  // displayed than the number of spaces in the previous level as to satisfy the width of each node (8 characters).
  std::function<int(int)> calcSpace;
  calcSpace = [&calcSpace] (int n) {
    return (n == 1) ? 0 : calcSpace(n - 1) + std::pow(2, n) * 2;
  };
  
  int level = static_cast<int> (1 + std::floor(std::log2(index))), children = 1, cur = 0, add = 0;
  for (Node* cursor = head; cursor != nullptr; cursor = cursor->next) {
    // If the number does not take up at least 3 characters, they are appended as spaces to the end of the node.
    if (cursor->val < 10)
      add++;

    if (cursor->val < 100)
      add++;
    
    if (cur % 2 != 0) {
      std::cout << "-" << cursor->val << " ";
      // The bottom-most level will *only* have one space between nodes.
      std::cout << std::string((level == 1) ? add : add + calcSpace(level), ' ');
      add = 0;
    } else {
      std::cout << cursor->val;
    }

    if (children <= ++cur) {
      // Grow children by 2^n
      children = cur * 2;
      cur = 0;
      level--;
      std::cout << std::endl;
    }
  }
  std::cout << std::endl << std::endl;
}
