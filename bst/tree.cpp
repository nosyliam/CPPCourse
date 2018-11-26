#include "tree.hpp"

int Tree::Node::depth() {
  int depth = 1;
  if (left)
    depth = 1 + left->depth();

  if (right)
    depth = (right->depth() + 1 > depth) ? 1 + right->depth() : depth;

  return depth;
}

Tree::Node::~Node() {
  Node*& dir = (parent->left == this) ? parent->left : parent->right;

  if (left && right) {
    // Find minimum node in the subtree
    Node* min = right;
    if (min->left != nullptr) {
      // Calculate the minimum node by descending left
      for (; min->left != nullptr; min = min->left) {};
    }

    // Swap positions with node
    if (min != right) {
      min->parent->left = nullptr;
      right->parent = min;
      min->right = right;
    }
    
    left->parent = min;
    min->parent = parent;
    min->left = left;
    dir = min;
    return;
  }
  
  // Destroy parent references to child
  dir = nullptr;
  if (left)
    dir = left;

  if (right)
    dir = right;
}

void Tree::insert(int val) {
  if (root->left == nullptr) {
    root->left = new Node(val, root);
    return;
  }

  auto dir = std::ref(root->left->left);
  Node* parent = root->left;
  while (true) {
    if (parent->key == val)
      return;
    
    if (parent->key > val) {
      dir = std::ref(parent->left);
      if (parent->left == nullptr)
	break;

      parent = parent->left;
      continue;
    }

    if (parent->key < val) {
      dir = std::ref(parent->right);
      if (parent->right == nullptr)
	break;

      parent = parent->right;
      continue;
    }
  }

  dir.get() = new Node(val, parent);
}

void Tree::remove(int val) {
  if (root->left == nullptr)
    return;
  
  Node* node = root->left;
  while (true) {
    if (node->key == val)
      break;

    if (node->key > val) {
      if (node->left == nullptr)
	return;

      node = node->left;
      continue;
    }

    if (node->key < val) {
      if (node->right == nullptr)
	break;

      node = node->right;
      continue;
    }
  }
  
  delete node;
}

void Tree::display() const {
  // To visualize the tree, we will use an algorithm which walks the parent node
  // and then it's right and left children. The height of the tree will be used to calculate
  // the spacing of the root node; as the tree is traversed, the location of parent nodes are
  // used to determine the location of child nodes
  if (!root->left)
    return;

  int depth = root->left->depth();
  char** out = new char*[depth];
  
  for (int n = 0; n < depth; n++) {
    out[n] = new char[501];
    memset(out[n], ' ', 500);
    out[n][500] = '\0';
  }

  std::function<int(int)> calculateSpacing;
  calculateSpacing = [&] (int n) {
    return (n > 0) ? calculateSpacing(n - 1) + (std::pow(2, n) * 1.5) : 0;
  };
  
  std::function<void(Node*, int, int, int)> walk;
  walk = [&] (Node* node, int level, int spacing, int dir) {
    spacing =   (dir == -1) ? spacing :
    /* right */ (dir == 0)  ? (!node->left  && depth - level != 1) ? spacing + 6 : spacing + ((calculateSpacing(depth - level) - 3) / 2) + 3
    /* left */              : (!node->right && depth - level != 1) ? spacing - 6 : spacing - ((calculateSpacing(depth - level) - 3) / 2) - 3;

    // Print number to buffer and copy
    char buf[4];
    memset(buf, '\0', sizeof(buf));
    sprintf(buf, "%d", node->val);
    memcpy(out[level] + spacing, buf, (node->val < 10) ? 1 : (node->val > 99) ? 3 : 2);

    // Traverse subtrees
    if (node->left)
      walk(node->left, level + 1, spacing, 1);
    

    if (node->right)
      walk(node->right, level + 1, spacing, 0);
    
  };
  
  // Traverse the tree and write to buffers as necessary. If we do not have an initial
  // left child, the root node's spacing is 0. If we do not have a right child, the
  // root's node spacing is 3 spaces ahead of the left child.
  int initial = calculateSpacing(depth - 1);
  if (!root->left->left)
    initial = 0;

  if (!root->left->right)
    initial -= ((calculateSpacing(depth - 1) - 3) / 2) - 6;
 
  walk(root->left, 0, initial, -1);

  // Normalize the tree. Start by finding the distance to the closest non-space character in the tree. In the process, fix the
  // location of the null terminator to the true end of the buffer.
  int dist = 500, cur = 0;
  char* cursor;
  for (int n = 0; n < depth; n++) {
    cur = 0;
    cursor = out[n];
    while (*cursor == ' ') {
      cursor++;
      cur++;
    }

    cursor = out[n] + 499;
    while (*cursor == ' ') {
      cursor--;
    }
    *(cursor + 1) = '\0';
    
    dist = (cur < dist) ? cur : dist;
  }

  // Fix the buffers
  for (int n = 0; n < depth; n++) {
    out[n] = out[n] + dist;
  }

  // Print out buffers
  for (int n = 0; n < depth; n++)
    printf("%s\n", out[n]);
}

