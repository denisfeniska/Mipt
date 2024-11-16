#include <iostream>

class Stack {
 private:
  int* values_;
  int size_;
  int capacity_;

  void AddCapacity() {
    int new_capacity = capacity_ * 2;
    int* new_values = new int[new_capacity];
    for (int i = 0; i < size_; ++i) {
      new_values[i] = values_[i];
    }
    delete[] values_;
    values_ = new_values;
    capacity_ = new_capacity;
  }

 public:
  Stack() : size_(0), capacity_(2) {
    values_ = new int[capacity_];
  }

  ~Stack() {
    delete[] values_;
  }

  void Push(int value) {
    if (size_ == capacity_) {
      AddCapacity();
    }
    values_[size_] = value;
    size_++;
  }

  int Pop() {
    if (size_ == 0) {
      return -1;
    }
    return values_[--size_];
  }

  int Top() {
    if (size_ == 0) {
      return -1;
    }
    return values_[size_ - 1];
  }

  int Size() {
    return size_;
  }

  void Clear() {
    size_ = 0;
  }
};

bool ValidSequence(char* sequence, int len) {
  Stack stack;
  for (int i = 0; i < len; ++i) {
    char elem = sequence[i];
    if (elem == '(') {
      stack.Push(elem);
    } else if (elem == ')') {
      if (stack.Size() == 0 || stack.Top() != '(') {
        return false;
      }
      stack.Pop();
    }
    if (elem == '[') {
      stack.Push(elem);
    } else if (elem == ']') {
      if (stack.Size() == 0 || stack.Top() != '[') {
        return false;
      }
      stack.Pop();
    }
    if (elem == '{') {
      stack.Push(elem);
    } else if (elem == '}') {
      if (stack.Size() == 0 || stack.Top() != '{') {
        return false;
      }
      stack.Pop();
    }
  }
  return stack.Size() == 0;
}

int main() {
  char* sequence = new char[100001];
  std::cin.getline(sequence, 100001);
  int len = 0;
  while (sequence[len] != '\0') {
    len++;
  }
  if (ValidSequence(sequence, len)) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }
  delete[] sequence;
  return 0;
}
