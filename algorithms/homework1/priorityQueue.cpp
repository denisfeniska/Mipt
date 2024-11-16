#include <iostream>

template <class T>
void Swap(T& a, T& b) {
  T temp = a;
  a = b;
  b = temp;
}

class PriorityQueue {
 private:
  int* values_;
  int max_size_;
  int size_;

  int SiftUp(int index) {
    while (index > 0) {
      int parent_index = (index - 1) / 2;
      if (values_[index] > values_[parent_index]) {
        Swap(values_[index], values_[parent_index]);
        index = parent_index;
      } else {
        break;
      }
    }
    return index;
  }

  int SiftDown(int index) {
    while (true) {
      int left_index = index * 2 + 1;
      int right_index = index * 2 + 2;
      int max_value_index = index;
      if (left_index < size_ && values_[max_value_index] < values_[left_index]) {
        max_value_index = left_index;
      }
      if (right_index < size_ && values_[max_value_index] < values_[right_index]) {
        max_value_index = right_index;
      }
      if (max_value_index == index) {
        return index + 1;
      }
      Swap(values_[index], values_[max_value_index]);
      index = max_value_index;
    }
  }

 public:
  void Init(int max_size) {
    max_size_ = max_size;
    values_ = new int[max_size];
    size_ = 0;
  }

  void Destructor() {
    delete[] values_;
  }

  void PopMax(int& final_position, int& max_value) {
    if (size_ == 0) {
      final_position = -1;
      max_value = -1;
      return;
    }
    max_value = values_[0];
    values_[0] = values_[size_ - 1];
    size_--;
    if (size_ == 0) {
      final_position = 0;
    } else {
      final_position = SiftDown(0);
    }
  }

  int AddElement(int value) {
    if (size_ == max_size_) {
      return -1;
    }
    values_[size_] = value;
    int index = size_;
    size_++;
    int final_position = SiftUp(index);
    return final_position + 1;
  }

  int Remove(int index) {
    index--;
    if (index < 0 || index >= size_) {
      return -1;
    }
    int removed_value = values_[index];
    values_[index] = values_[size_ - 1];
    size_--;
    if (index < size_) {
      SiftDown(index);
      SiftUp(index);
    }
    return removed_value;
  }

  void Print() {
    for (int i = 0; i < size_; ++i) {
      std::cout << values_[i] << " ";
    }
    std::cout << "\n";
  }
};

int main() {
  int queue_size = 0;
  int count_commands = 0;
  std::cin >> queue_size >> count_commands;
  PriorityQueue queue;
  queue.Init(queue_size);
  for (int i = 0; i < count_commands; ++i) {
    int type = 0;
    std::cin >> type;
    if (type == 1) {
      int final_position = 0;
      int max_value = 0;
      queue.PopMax(final_position, max_value);
      if (final_position == -1) {
        std::cout << -1 << "\n";
      } else {
        std::cout << final_position << " " << max_value << "\n";
      }
    } else if (type == 2) {
      int value = 0;
      std::cin >> value;
      int new_tree = queue.AddElement(value);
      if (new_tree == -1) {
        std::cout << -1 << "\n";
      } else {
        std::cout << new_tree << "\n";
      }
    } else if (type == 3) {
      int index = 0;
      std::cin >> index;
      int new_tree = queue.Remove(index);
      if (new_tree == -1) {
        std::cout << -1 << "\n";
      } else {
        std::cout << new_tree << "\n";
      }
    }
  }
  queue.Print();
  queue.Destructor();
  return 0;
}