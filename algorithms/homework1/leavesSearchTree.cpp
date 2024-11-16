#include <iostream>

template <class T, class U, class R>
void Merge(const T* first_begin, const T* first_end, const U* second_begin, const U* second_end, R* out) {
  while (first_begin < first_end && second_begin < second_end) {
    if (*first_begin < *second_begin) {
      *out = *first_begin;
      ++first_begin;
      ++out;
    } else {
      *out = *second_begin;
      ++second_begin;
      ++out;
    }
  }
  while (first_begin < first_end) {
    *out = *first_begin;
    ++first_begin;
    ++out;
  }
  while (second_begin < second_end) {
    *out = *second_begin;
    ++second_begin;
    ++out;
  }
}

template <class T>
void Sort(T* begin, T* end) {
  if (end - begin <= 1) {
    return;
  }
  T* mid = begin + (end - begin) / 2;
  Sort(begin, mid);
  Sort(mid, end);
  T* temp = new T[end - begin];
  Merge(begin, mid, mid, end, temp);
  for (int i = 0; i < end - begin; ++i) {
    begin[i] = temp[i];
  }
  delete[] temp;
}

struct TreeNode {
  TreeNode* left;
  TreeNode* right;
  int value;
  explicit TreeNode(int val) {
    value = val;
    right = nullptr;
    left = nullptr;
  }
};

void Insert(TreeNode*& root, int value) {
  if (!root) {
    root = new TreeNode(value);
  } else if (value < root->value) {
    Insert(root->left, value);
  } else if (value > root->value) {
    Insert(root->right, value);
  }
}

void Leaves(TreeNode* root, int* leaves_arr, int& index) {
  if (!root) {
    return;
  }
  if (!root->left && !root->right) {
    leaves_arr[index++] = root->value;
  }
  if (root->left) {
    Leaves(root->left, leaves_arr, index);
  }
  if (root->right) {
    Leaves(root->right, leaves_arr, index);
  }
}

void PrintLeaves(TreeNode* root, int count) {
  int* leaves_arr = new int[count];
  int index = 0;
  Leaves(root, leaves_arr, index);
  Sort(leaves_arr, leaves_arr + index);
  for (int i = 0; i < index; ++i) {
    std::cout << leaves_arr[i] << " ";
  }
  std::cout << "\n";
  delete[] leaves_arr;
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
  int elem = 0;
  int count = 0;
  TreeNode* root = nullptr;
  while (true) {
    std::cin >> elem;
    if (elem == 0) {
      break;
    }
    Insert(root, elem);
    count++;
  }
  PrintLeaves(root, count);
  ClearMemory(root);
  return 0;
}