#include <iostream>

class QueueWithMin {
 private:
  int* left_stack_;
  int* left_min_;
  int* right_stack_;
  int* right_min_;
  int left_size_;
  int right_size_;
  int left_capacity_;
  int right_capacity_;

  void LeftToRight() {
    while (left_size_ > 0) {
      int value = left_stack_[--left_size_];
      int new_min = 1000000001;
      if (right_size_ == 0) {
        new_min = value;
      } else {
        new_min = (value <= right_min_[right_size_ - 1]) ? value : right_min_[right_size_ - 1];
      }
      if (right_size_ == right_capacity_) {
        AddRightCapacity();
      }
      right_stack_[right_size_] = value;
      right_min_[right_size_] = new_min;
      right_size_++;
    }
  }

  void AddLeftCapacity() {
    left_capacity_ = left_capacity_ * 2;
    int* new_left_stack = new int[left_capacity_];
    int* new_left_min = new int[left_capacity_];
    for (int i = 0; i < left_size_; i++) {
      new_left_stack[i] = left_stack_[i];
      new_left_min[i] = left_min_[i];
    }
    delete[] left_stack_;
    delete[] left_min_;
    left_stack_ = new_left_stack;
    left_min_ = new_left_min;
  }

  void AddRightCapacity() {
    right_capacity_ = right_capacity_ * 2;
    int* new_right_stack = new int[right_capacity_];
    int* new_right_min = new int[right_capacity_];
    for (int i = 0; i < right_size_; i++) {
      new_right_stack[i] = right_stack_[i];
      new_right_min[i] = right_min_[i];
    }
    delete[] right_stack_;
    delete[] right_min_;
    right_stack_ = new_right_stack;
    right_min_ = new_right_min;
  }

 public:
  QueueWithMin() : left_size_(0), right_size_(0), left_capacity_(2), right_capacity_(2) {
    left_stack_ = new int[left_capacity_];
    left_min_ = new int[left_capacity_];
    right_stack_ = new int[right_capacity_];
    right_min_ = new int[right_capacity_];
  }

  ~QueueWithMin() {
    delete[] left_stack_;
    delete[] left_min_;
    delete[] right_stack_;
    delete[] right_min_;
  }

  void Enqueue(int number) {
    if (left_size_ == left_capacity_) {
      AddLeftCapacity();
    }
    left_stack_[left_size_] = number;
    if (left_size_ == 0) {
      left_min_[left_size_] = number;
    } else {
      left_min_[left_size_] = (number <= left_min_[left_size_ - 1]) ? number : left_min_[left_size_ - 1];
    }
    left_size_++;
  }

  void Dequeue() {
    if (right_size_ == 0) {
      if (left_size_ == 0) {
        return;
      }
      LeftToRight();
    }
    --right_size_;
  }

  void Min() {
    if (left_size_ == 0 && right_size_ == 0) {
      std::cout << "error\n";
      return;
    }
    int min_left = (left_size_ == 0) ? 1000000001 : left_min_[left_size_ - 1];
    int min_right = (right_size_ == 0) ? 1000000001 : right_min_[right_size_ - 1];
    std::cout << (min_left < min_right ? min_left : min_right) << "\n";
  }
};

int main() {
  QueueWithMin queue;
  int count = 0;
  int window = 0;
  std::cin >> count >> window;
  int* arr = new int[count];
  for (int i = 0; i < count; ++i) {
    std::cin >> arr[i];
  }
  for (int i = 0; i < window; ++i) {
    queue.Enqueue(arr[i]);
  }
  queue.Min();
  for (int i = window; i < count; ++i) {
    queue.Dequeue();
    queue.Enqueue(arr[i]);
    queue.Min();
  }
  delete[] arr;
  return 0;
}