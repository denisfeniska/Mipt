#include <iostream>

class Queue {
 private:
  int* values_;
  int head_;
  int tail_;
  int size_;
  int capacity_;

  void AddCapacity() {
    int new_capacity = capacity_ * 2;
    int* new_values = new int[new_capacity];
    for (int i = 0; i < size_; ++i) {
      new_values[i] = values_[(head_ + i) % capacity_];
    }
    delete[] values_;
    values_ = new_values;
    head_ = 0;
    tail_ = size_;
    capacity_ = new_capacity;
  }

 public:
  Queue() : head_(0), tail_(0), size_(0), capacity_(6) {
    values_ = new int[capacity_];
  }

  ~Queue() {
    delete[] values_;
  }

  void Enqueue(int value) {
    if (size_ == capacity_) {
      AddCapacity();
    }
    values_[tail_] = value;
    tail_ = (tail_ + 1) % capacity_;
    size_++;
  }

  int Dequeue() {
    if (size_ == 0) {
      return -1;
    }
    int removed_value = values_[head_];
    head_ = (head_ + 1) % capacity_;
    size_--;
    return removed_value;
  }

  int Size() {
    return size_;
  }
};

bool CheckHigherCard(int first_card, int second_card) {
  if (first_card == 9) {
    if (second_card == 0) {
      return false;
    }
  }
  if (second_card == 9) {
    if (first_card == 0) {
      return true;
    }
  }
  return first_card > second_card;
}

int main() {
  Queue first_queue;
  Queue second_queue;
  int first_cards[5];
  int second_cards[5];
  for (int i = 0; i < 5; ++i) {
    int value = 0;
    std::cin >> value;
    first_cards[i] = value;
    first_queue.Enqueue(value);
  }
  for (int i = 0; i < 5; ++i) {
    int value = 0;
    std::cin >> value;
    second_cards[i] = value;
    second_queue.Enqueue(value);
  }
  int count = 0;
  while (first_queue.Size() != 0 && second_queue.Size() != 0 && count != 1000000) {
    int first_card = first_queue.Dequeue();
    int second_card = second_queue.Dequeue();
    if (CheckHigherCard(first_card, second_card)) {
      first_queue.Enqueue(first_card);
      first_queue.Enqueue(second_card);
    } else {
      second_queue.Enqueue(first_card);
      second_queue.Enqueue(second_card);
    }
    count++;
  }
  if (count == 1000000) {
    std::cout << "botva"
              << "\n";
  } else if (second_queue.Size() == 0) {
    std::cout << "first"
              << " " << count << "\n";
  } else {
    std::cout << "second"
              << " " << count << "\n";
  }
  return 0;
}