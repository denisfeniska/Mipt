#include <iostream>

struct Node {
  int value;
  int height;
  Node* left;
  Node* right;

  explicit Node(int number) : value(number), height(1), left(nullptr), right(nullptr) {
  }
};

class AvlTree {
 private:
  Node* root_;

  int Height(Node* node) {
    if (node) {
      return node->height;
    }
    return 0;
  }

  void NewHeight(Node* node) {
    if (!node) {
      return;
    }
    int max_height = std::max(Height(node->left), Height(node->right));
    node->height = max_height + 1;
  }

  Node* SmallRotateRight(Node* node) {
    Node* new_root = node->left;
    node->left = new_root->right;
    new_root->right = node;
    NewHeight(node);
    NewHeight(new_root);
    return new_root;
  }

  Node* SmallRotateLeft(Node* node) {
    Node* new_root = node->right;
    node->right = new_root->left;
    new_root->left = node;
    NewHeight(node);
    NewHeight(new_root);
    return new_root;
  }

  Node* Balance(Node* node) {
    NewHeight(node);
    if (Height(node->right) - Height(node->left) == 2) {
      if (Height(node->right->left) > Height(node->right->right)) {
        node->right = SmallRotateRight(node->right);
      }
      return SmallRotateLeft(node);
    }
    if (Height(node->left) - Height(node->right) == 2) {
      if (Height(node->left->right) > Height(node->left->left)) {
        node->left = SmallRotateLeft(node->left);
      }
      return SmallRotateRight(node);
    }
    return node;
  }

  Node* Add(Node* node, int number) {
    if (!node) {
      return new Node(number);
    }
    if (number < node->value) {
      node->left = Add(node->left, number);
    } else if (number > node->value) {
      node->right = Add(node->right, number);
    }
    return Balance(node);
  }

  int Next(Node* node, int number) {
    Node* temp = node;
    int res = 0;
    while (temp) {
      if (temp->value >= number) {
        res = temp->value;
        temp = temp->left;
      } else {
        temp = temp->right;
      }
    }
    if (res == 0) {
      return -1;
    }
    return res;
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
  AvlTree() : root_(nullptr) {
  }

  ~AvlTree() {
    ClearTree(root_);
  }

  void Add(int number) {
    root_ = Add(root_, number);
  }

  int Next(int number) {
    return Next(root_, number);
  }
};

int main() {
  int count = 0;
  std::cin >> count;
  int prev_elem = '0';
  int prev = 0;
  int number = 0;
  AvlTree tree;
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