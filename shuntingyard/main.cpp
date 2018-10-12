#include <cstring>
#include <iostream>
#include "stack.hpp"
#include "node.hpp"

inline int getPrec(char op) {
  return (op == '^') ? 4 : (op == '*' || op == '/') ? 3 : 2;
}

inline int isOperator(char op) {
  return (op == '+' || op == '-' || op == '*' || op == '/' || op == '^');
}

void recurseInfix(Node* root) {
  if (!root)
    return;
  
  if (isOperator(root->Value()[0]))
    std::cout << '(' << " ";
  
  recurseInfix(root->Left());
  std::cout << root->Value() << " ";
  recurseInfix(root->Right());
  
  if (isOperator(root->Value()[0]))
    std::cout << ')' << " ";
}

void recursePostfix(Node* root) {
  if (!root)
    return;

  recursePostfix(root->Left());
  recursePostfix(root->Right());
  std::cout << root->Value() << " ";
}

void recursePrefix(Node* root) {
  if (!root)
    return;

  std::cout << root->Value() << " ";
  recursePrefix(root->Left());
  recursePrefix(root->Right());
}

Node* compilePostfix(char* input) {
  Stack<Node*> tree;

  for (int cursor = 0, tok = 0; input[cursor] != '\0'; cursor++, tok++) {
    if (input[cursor] != ' ')
      continue;

    char head = input[cursor - tok];
    
    switch (head) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
      {
	// Allocate node with char array and set the last byte to a null terminator
	Node* parent = new Node((char *) memset(memcpy(new char[tok + 1], input + cursor - tok, tok) + tok, '\0', 1) - tok);
        Node* right = tree.pop();
        Node* left = tree.pop();
	// Top two nodes are popped and set as children of a new parent node
        parent->setLeft(left);
        parent->setRight(right);
        tree.push(parent);
      };
      break;
    default:
      tree.push(new Node((char *) memset(memcpy(new char[tok + 1], input + cursor - tok, tok) + tok, '\0', 1) - tok));
    }
    
    tok = -1;
  }
  return tree.pop();
}

char* compileInfix(char* input) {
  char* output = new char[strlen(input)];
  char* outcursor = output;
  memset(output, ' ', strlen(input));
  Stack<char> ops;

  for (int cursor = 0, tok = 0; input[cursor] != '\0'; cursor++, tok++) {
    if (input[cursor] != ' ')
      continue;

    char head = input[cursor - tok];

    switch (head) {
    case '-':
    case '+':
    case '*':
    case '/':
    case '^':
      if (tok > 1)
	return nullptr; // malformed operator

      // If the operator at the top of the stack has greater precedence, equal precedence
      // and is left-associate, or a left-bracket pop the operator onto the output queue
      if (!ops.empty()) {
	while (!ops.empty())
	  if (getPrec(ops.peek()) > getPrec(head) || ((getPrec(ops.peek()) == getPrec(head)) && ops.peek() != '^') && ops.peek() != '(') {
	    *(outcursor++) = ops.pop();
	    outcursor++;
          } else {
	    break;
	  }
      }

      ops.push(head);
      break;
    case '(':
      if (tok > 1)
	return nullptr;

      ops.push(head);
      break;
    case ')':
      if (tok > 1)
	return nullptr;

      // Pop operators until left bracket is reached
      while (!ops.empty()) {
	if (ops.peek() == '(')
	  break;

	*(outcursor++) = ops.pop();
	outcursor++;
      }

      // Pop the left bracket from the stack
      ops.pop();
      break;
    default:
      // If number, write to output
      outcursor = (char *) memcpy(outcursor, input + cursor - tok, tok) + tok + 1;
    }

    tok = -1;
  }

  while (!ops.empty()) {
    *(outcursor++) = ops.pop();
    outcursor++;
  }

  *outcursor = '\0';
  return output;
  
}

int main() {
  char buf[255];

  std::cout << "Enter mathematical expression: ";
  std::cin.getline(buf, sizeof(buf));

  // Compile to postfix, build expression tree, and print
  char* infix = compileInfix(buf);
  Node* postfix = compilePostfix(infix);
  std::cout << "Infix: ";
  recurseInfix(postfix);
  std::cout << std::endl << "Postfix: ";
  recursePostfix(postfix);
  std::cout << std::endl << "Prefix: ";
  recursePrefix(postfix);
}
