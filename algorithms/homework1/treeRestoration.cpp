#include <iostream>
#include <climits>

struct TreeNode {
  int value;
  TreeNode* left;
  TreeNode* right;
  explicit TreeNode(int val) : value(val), left(nullptr), right(nullptr) {
  }
};

TreeNode* PreOrderTree(int* preorder_arr, int& index, int min_value, int max_value, int count) {
  if (index >= count || preorder_arr[index] < min_value || preorder_arr[index] > max_value) {
    return nullptr;
  }
  auto root = new TreeNode(preorder_arr[index++]);
  root->left = PreOrderTree(preorder_arr, index, min_value, root->value, count);
  root->right = PreOrderTree(preorder_arr, index, root->value, max_value, count);
  return root;
}

void PostOrderTree(TreeNode* root, int* result, int& index) {
  if (!root) {
    return;
  }
  PostOrderTree(root->left, result, index);
  PostOrderTree(root->right, result, index);
  result[index++] = root->value;
}

void DeleteTree(TreeNode* root) {
  if (!root) {
    return;
  }
  DeleteTree(root->left);
  DeleteTree(root->right);
  delete root;
}

int main() {
  int count = 0;
  std::cin >> count;
  if (count == 0) {
    return 0;
  }
  int* preorder_arr = new int[count];
  for (int i = 0; i < count; ++i) {
    std::cin >> preorder_arr[i];
  }
  int index_preorder = 0;
  TreeNode* root = PreOrderTree(preorder_arr, index_preorder, INT_MIN, INT_MAX, count);
  if (index_preorder != count) {
    return 0;
  }
  int* result = new int[count];
  int index_postorder = 0;
  PostOrderTree(root, result, index_postorder);
  for (int i = 0; i < count; ++i) {
    std::cout << result[i] << " ";
  }
  std::cout << "\n";
  delete[] preorder_arr;
  delete[] result;
  DeleteTree(root);
  return 0;
}