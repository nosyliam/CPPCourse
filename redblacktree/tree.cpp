#include "tree.hpp"

void Tree::rotateLeft(Node* n) {
  if (!n->right)
    throw;

  Node* base = n->right, *parent = n->parent;
  n->right = base->left;
  base->left = n;
  n->parent = base;
  
  if (n->right)
    n->right->parent = n;

  if (parent) {
    if (n == parent->left) {
      parent->left = base;
    } else {
      parent->right = base;
    }
  }

  base->parent = parent;
}

void Tree::rotateRight(Node* n) {
  if (!n->left)
    throw;

  Node* base = n->left, *parent = n->parent;
  n->left = base->right;
  base->right = n;
  n->parent = base;

  if (n->left)
    n->left->parent = n;

  if (parent) {
    if (n == parent->left) {
      parent->left = base;
    } else {
      parent->right = base;
    }
  }

  base->parent = parent;
}

void Tree::insert(int n) {
  Node* node = new Node(n);
  if (!root) {
    // Insert the node as the root (child of the sentinel node)
    root = node;
    repaintTree(node);
    return;
  }

  // Traverse the tree in-order to find a suitable location for the node
  Node* parent = root;
  for (;;) {
    if (!parent)
      break;
    
    if (n < parent->value) {
      if (parent->left) {
	parent = parent->left;
	continue;
      } else {
	parent->left = node;
	break;
      }
    } else {
      if (parent->right) {
	parent = parent->right;
	continue;
      } else {
	parent->right = node;
	break;
      }
    }
  }

  node->parent = parent;
  repaintTree(node);

  root = node;
  while (root->parent)
    root = root->parent;
}

void Tree::remove(int n) {
  Node* base = find(n, root);
  if (!base)
    return;

  // No children
  if (!base->left && !base->right) {
    if (base->parent->left == base) {
      base->parent->left = nullptr;
    } else {
      base->parent->right = nullptr;
    }
    
    delete base;
    return;
  }

  // Two non-leaf children
  if (base->left && base->right) {
    // Find the minimum node in the right subtree
    Node* min = base->right;
    while (min->left)
      min = min->left;

    // Replace node's value with the node
    base->value = min->value;
    if (min->right) {
      // The node has a right child, handle it appropriately
      removeOneChild(min);
      return;
    }

    // The node has no children; discard of it
    if (min->parent->left == min) {
      min->parent->left = nullptr;
    } else {
      min->parent->right = nullptr;
    }

    delete min;
    
    return;
  }
    

  // One non-leaf child
  removeOneChild(base); 
}

void Tree::removeOneChild(Node* base) {
  Node* child = (!base->right) ? base->left : base->right;
  // Swap parent and child
  child->parent = base->parent;
  if ((base->parent) && base == base->parent->left) {
    base->parent->left = child;
  } else if (base->parent) {
    base->parent->right = child;
  }

  if (base->color == Color::Black) {
    if (child->color == Color::Red) {
      child->color = Color::Black;
      goto finish;
    } else {
      goto case1;
    }
  }

  // Convenience variables
  Node* s;
  
 case1:
  if (child->parent) {
    goto case2;
  } else {
    goto finish;
  }

 case2:
  s = child->sibling();
  if ((s) && s->color == Color::Red) {
    child->parent->color = Color::Red;
    s->color = Color::Black;
    if (child == child->parent->left) {
      rotateLeft(child->parent);
    } else {
      rotateRight(child->parent);
    }
  }
  
  goto case3;
 case3:
  s = child->sibling();
  if ((s) && (child->parent->color == Color::Black) &&
      (s->color == Color::Black) &&
      ((!s->left) || s->left->color == Color::Black) &&
      ((!s->right) || s->right->color == Color::Black)) {
    s->color = Color::Red;
    child = child->parent;
    goto case1;
  } else {
    goto case4;
  }
  
 case4:
  s = child->sibling();
  if ((s) && (child->parent->color == Color::Red) &&
      (s->color == Color::Black) &&
      ((!s->left) || s->left->color == Color::Black) &&
      ((!s->right) || s->right->color == Color::Black)) {
    s->color = Color::Red;
    child->parent->color = Color::Black;
    goto finish;
  } else {
    goto case5;
  }
  
 case5:
  s = child->sibling();
  if ((s) && s->color == Color::Black) {
    if ((child == child->parent->left) &&
	((!s->right) || s->right->color == Color::Black) &&
	((!s->left) || s->left->color == Color::Red)) {
      s->color = Color::Red;
      s->left->color = Color::Black;
      rotateRight(s);
    } else if ((child == child->parent->right) &&
	       ((!s->left) || s->left->color == Color::Black) &&
               ((!s->right) || s->right->color == Color::Red)) {
      s->color = Color::Red;
      s->right->color = Color::Black;
      rotateLeft(s);
    }
  }
  goto case6;
 case6:
  s = child->sibling();
  if (!s)
    goto finish;
  
  s->color = child->parent->color;
  child->parent->color = Color::Black;

  if (child == child->parent->left) {
    if (s->right)
      s->right->color = Color::Black;
    rotateLeft(child->parent);
  } else {
    if (s->left)
      s->left->color = Color::Black;
    rotateRight(child->parent);
  }
 finish:
  while (root->parent)
    root = root->parent;
  
  delete base;
}

bool Tree::search(int n) {
  return find(n, root) ? true : false;
}

Tree::Node* Tree::find(int n, Node* base) {
  if ((!base) || base->value == n)
    return base;

  Node *found;
  if ((base->left) && n < base->value) {
    found = find(n, base->left);
    return (found) ? found : find(n, base->right);
  } else if (base->right) {
    found = find(n, base->right);
    return (found) ? found : find(n, base->left);
  }
  
  return nullptr;
}

void Tree::repaintTree(Node* n) {
  if (!n->parent) {
    n->color = Color::Black;
  } else if (n->parent->color == Color::Black) {
    return;
  } else if ((n->uncle()) && n->uncle()->color == Color::Red) {
    // If the parent and it's siblings are red, we can repair the tree so that
    // they are both black. This will satisfy the rule that colors must alternate, but
    // may violate the rule that the root is always black. To repair this, we can repaint
    // the tree upwards from the grandparent.
    n->parent->color = Color::Black;
    n->uncle()->color = Color::Black;
    n->grandparent()->color = Color::Red;
    repaintTree(n->grandparent());
  } else {
    // In this case, the parent is red but it's sibling is black. To repair this, we want to
    // move the current node into the grandparent position. We start by switching the roles of
    // the node and the parent (via tree rotation). We then rotate the grandparent so that the
    // parent node takes it's role; because we know the grandparent is black and the parent
    // is red, we can switch the colors of the grandparent and parent.

    
    if ((n->grandparent()->left) && n == n->grandparent()->left->right) {
      rotateLeft(n->parent);
      n = n->left;
    } else if ((n->grandparent()->right) && n == n->grandparent()->right->left) {
      rotateRight(n->parent);
      n = n->right;
    }

    Node* p = n->parent;
    Node* g = n->grandparent();
    
    if (n == p->left) {
      rotateRight(g);
    } else {
      rotateLeft(g);
    }

    p->color = Color::Black;
    g->color = Color::Red;
  }
}

void Tree::display() const {
  // To visualize the tree, we will use an algorithm which walks the parent node
  // and then it's right and left children. The height of the tree will be used to calculate
  // the spacing of the root node; as the tree is traversed, the location of parent nodes are
  // used to determine the location of child nodes
  if (!root)
    return;

  int depth = root->depth();
  char** out = new char*[depth];

  for (int n = 0; n < depth; n++) {
    out[n] = new char[502];
    memset(out[n], ' ', 500);
    out[n][500] = '\0';
    // Store extra byte to hold color-spacing counter
    out[n][501] = 0;
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

    // For the visualization to display correctly with colors, we need a counter to account for
    // the extra space added by the escape codes. To this, we use the last byte at the end of the buffer
    // which holds the number of nodes previously displayed within it.
    char colorSpacing = out[level][501]++ * 5;
    
    // Print number to buffer and copy
    char buf[4];
    memset(buf, '\0', sizeof(buf));
    sprintf(buf, "\33[%dm%d", (node->color == Color::Black) ? 34 : 31, node->value);
    memcpy(out[level] + spacing + colorSpacing, buf, (node->value < 10) ? 6 : (node->value > 99) ? 8 : 7);

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
  if (!root->left)
    initial = 0;

  if (!root->right)
    initial -= ((calculateSpacing(depth - 1) - 3) / 2) - 6;

  walk(root, 0, initial, -1);

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
  for (int n = 0; n < depth; n++) {
    printf("%s\n", out[n]);
  }

  std::cout << "\033[0m";
}
