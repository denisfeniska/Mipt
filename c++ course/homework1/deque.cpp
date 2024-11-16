#include <iostream>

class Deque {
 public:
  int* nums;
  int size;
  int head;
  int tail;
  int count;
  void AddSize() {
    int new_size = size * 2;
    int* new_nums = new int[new_size];
    for (int i = 0; i < count; ++i) {
      new_nums[i] = nums[(head + i) % size];
    }
    delete[] nums;
    nums = new_nums;
    size = new_size;
    head = 0;
    tail = count;
  }

  void PushFront(int number) {
    if (size == count) {
      AddSize();
    }
    head = (head - 1 + size) % size;
    nums[head] = number;
    ++count;
    std::cout << "ok"
              << "\n";
  }

  void PushBack(int number) {
    if (size == count) {
      AddSize();
    }
    nums[tail] = number;
    tail = (tail + 1) % size;
    ++count;
    std::cout << "ok"
              << "\n";
  }

  void PopFront() {
    if (count == 0) {
      std::cout << "error"
                << "\n";
    } else {
      std::cout << nums[head] << "\n";
      head = (head + 1) % size;
      --count;
    }
  }

  void PopBack() {
    if (count == 0) {
      std::cout << "error"
                << "\n";
    } else {
      tail = (tail - 1 + size) % size;
      std::cout << nums[tail] << "\n";
      --count;
    }
  }

  void Front() {
    if (count == 0) {
      std::cout << "error"
                << "\n";
    } else {
      std::cout << nums[head] << "\n";
    }
  }

  void Back() {
    if (count == 0) {
      std::cout << "error"
                << "\n";
    } else {
      std::cout << nums[(tail - 1 + size) % size] << "\n";
    }
  }

  void Size() {
    std::cout << count << "\n";
  }

  void Clear() {
    head = 0;
    tail = 0;
    count = 0;
    std::cout << "ok"
              << "\n";
  }
};

bool CompareStrings(const char* str1, const char* str2) {
  while (*str1 && str2) {
    if (*str1 != *str2) {
      return false;
    }
    ++str1;
    ++str2;
  }
  return (*str1 == '\0' && *str2 == '\0');
}

int main() {
  int k_count = 0;
  std::cin >> k_count;
  Deque deque;
  deque.size = 4;
  deque.head = 0;
  deque.tail = 0;
  deque.count = 0;
  deque.nums = new int[deque.size];
  for (int i = 0; i < k_count; ++i) {
    char command[50];
    std::cin >> command;
    if (CompareStrings(command, "push_front")) {
      int number = 0;
      std::cin >> number;
      deque.PushFront(number);
    } else if (CompareStrings(command, "push_back")) {
      int number = 0;
      std::cin >> number;
      deque.PushBack(number);
    } else if (CompareStrings(command, "pop_front")) {
      deque.PopFront();
    } else if (CompareStrings(command, "pop_back")) {
      deque.PopBack();
    } else if (CompareStrings(command, "front")) {
      deque.Front();
    } else if (CompareStrings(command, "back")) {
      deque.Back();
    } else if (CompareStrings(command, "size")) {
      deque.Size();
    } else if (CompareStrings(command, "clear")) {
      deque.Clear();
    } else if (CompareStrings(command, "exit")) {
      std::cout << "bye"
                << "\n";
      break;
    }
  }
  delete[] deque.nums;
  return 0;
}