#include <iostream>

struct Node {
  int value;
  int height;
  Node* left;
  Node* right;

  explicit Node(int number) : value(number), height(1), left(nullptr), right(nullptr) {
  }
};

class SplayTree {
 private:
  Node* root_;

  Node* Zig(Node* node) {
    Node* new_root = node->left;
    node->left = new_root->right;
    new_root->right = node;
    return new_root;
  }

  Node* Zag(Node* node) {
    Node* new_root = node->right;
    node->right = new_root->left;
    new_root->left = node;
    return new_root;
  }

  Node* ZigZag(Node* node) {
    node->left = Zag(node->left);
    return Zig(node);
  }

  Node* ZagZig(Node* node) {
    node->right = Zag(node->right);
    return Zag(node);
  }

  Node* Splay(Node* root, int number) {
    if (!root) {
      return root;
    }
    if (root->value == number) {
      return root;
    }
    if (root->value > number) {
      if (!root->left) {
        return root;
      }
      if (root->left->value > number) {
        root->left->left = Splay(root->left->left, number);
        root = Zig(root);
      } else if (root->left->value < number) {
        root->left->right = Splay(root->left->right, number);
        if (root->left->right) {
          root->left = Zag(root->left);
        }
      }
      if (root->left) {
        return Zig(root);
      }
      return root;
    }
    if (!root->right) {
      return root;
    }
    if (root->right->value < number) {
      root->right->right = Splay(root->right->right, number);
      root = Zag(root);
    } else if (root->right->value > number) {
      root->right->left = Splay(root->right->left, number);
      if (root->right->left) {
        root->right = Zig(root->right);
      }
    }
    if (root->right) {
      return Zag(root);
    }
    return root;
  }

  Node* Add(Node* root, int number) {
    if (!root) {
      return new Node(number);
    }
    root = Splay(root, number);
    if (root->value == number) {
      return root;
    }
    Node* new_node = new Node(number);
    if (root->value > number) {
      new_node->right = root;
      new_node->left = root->left;
      root->left = nullptr;
    } else {
      new_node->left = root;
      new_node->right = root->right;
      root->right = nullptr;
    }
    return new_node;
  }

  Node* Next(Node* root, int number) {
    Node* temp = nullptr;
    while (root) {
      if (root->value >= number) {
        temp = root;
        root = root->left;
      } else {
        root = root->right;
      }
    }
    return temp;
  }

  void ClearTree(Node* node) {
    if (!node) {
      return;
    }
    ClearTree(node->left);
    ClearTree(node->right);
    delete node;
  }

 public:
  SplayTree() : root_(nullptr) {
  }

  ~SplayTree() {
    ClearTree(root_);
  }

  void Add(int number) {
    root_ = Add(root_, number);
  }

  int Next(int number) {
    Node* temp = Next(root_, number);
    if (temp) {
      return temp->value;
    }
    return -1;
  }
};

int main() {
  int count = 0;
  std::cin >> count;
  int prev_elem = '0';
  int prev = 0;
  int number = 0;
  SplayTree tree;
  for (int i = 0; i < count; ++i) {
    char elem = '0';
    std::cin >> elem >> number;
    if (elem == '+') {
      if (prev_elem == '?') {
        number = (number + prev) % 1'000'000'000;
      }
      tree.Add(number);
    } else if (elem == '?') {
      prev = tree.Next(number);
      std::cout << prev << "\n";
    }
    prev_elem = elem;
  }
  return 0;
}