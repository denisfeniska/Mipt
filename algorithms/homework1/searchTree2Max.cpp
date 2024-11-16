#include <iostream>

struct TreeNode {
  int value;
  TreeNode* left;
  TreeNode* right;
  void Constructor(int val) {
    value = val;
    left = nullptr;
    right = nullptr;
  }
};

void Insert(TreeNode*& root, int value) {
  if (!root) {
    root = new TreeNode;
    root->Constructor(value);
  } else if (value < root->value) {
    Insert(root->left, value);
  } else if (value > root->value) {
    Insert(root->right, value);
  }
}

int SecondMax(TreeNode* root) {
  TreeNode* parent = nullptr;
  TreeNode* current = root;
  while (current && current->right) {
    parent = current;
    current = current->right;
  }
  if (current && current->left) {
    current = current->left;
    while (current->right) {
      current = current->right;
    }
    return current->value;
  }
  return parent->value;
}

void ClearMemory(TreeNode* root) {
  if (!root) {
    return;
  }
  ClearMemory(root->left);
  ClearMemory(root->right);
  delete root;
}

int main() {
  int value = 0;
  TreeNode* root = nullptr;
  while (true) {
    std::cin >> value;
    if (value == 0) {
      break;
    }
    Insert(root, value);
  }
  std::cout << SecondMax(root) << "\n";
  ClearMemory(root);
  return 0;
}