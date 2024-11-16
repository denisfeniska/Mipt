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

int main() {
  char elem = '0';
  Stack stack;
  while (std::cin >> elem) {
    if (elem == '-' || elem == '+' || elem == '*') {
      if (stack.Size() < 2) {
        return 0;
      }
      int second = stack.Pop();
      int first = stack.Pop();
      if (elem == '+') {
        stack.Push(first + second);
      } else if (elem == '-') {
        stack.Push(first - second);
      } else {
        stack.Push(first * second);
      }
    } else if (elem == ' ') {
      continue;
    } else {
      int elem_int = elem - '0';
      stack.Push(elem_int);
    }
  }
  std::cout << stack.Top() << "\n";
}