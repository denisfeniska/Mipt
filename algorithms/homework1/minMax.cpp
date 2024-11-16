#include <iostream>

template <class T>
void Swap(T& a, T& b) {
  T temp = a;
  a = b;
  b = temp;
}

class MinMax {
 private:
  int* max_heap_;
  int* min_heap_;
  int max_size_;
  int size_max_heap_;
  int size_min_heap_;

  int SiftUp(int* heap, int index, bool is_max_heap) {
    while (index > 0) {
      int parent_index = (index - 1) / 2;
      if ((is_max_heap && heap[index] > heap[parent_index]) || 
          (!is_max_heap && heap[index] < heap[parent_index])) {
        Swap(heap[index], heap[parent_index]);
        index = parent_index;
      } else {
        break;
      }
    }
    return index;
  }

  int SiftDown(int* heap, int size, int index, bool is_max_heap) {
    while (true) {
      int left_index = index * 2 + 1;
      int right_index = index * 2 + 2;
      int target_index = index;
      if (left_index < size &&
          ((is_max_heap && heap[target_index] < heap[left_index]) || 
           (!is_max_heap && heap[target_index] > heap[left_index]))) {
        target_index = left_index;
      }
      if (right_index < size &&
          ((is_max_heap && heap[target_index] < heap[right_index]) || 
           (!is_max_heap && heap[target_index] > heap[right_index]))) {
        target_index = right_index;
      }
      if (target_index == index) {
        return index + 1;
      }
      Swap(heap[index], heap[target_index]);
      index = target_index;
    }
  }

 public:
  void Init(int max_size) {
    max_size_ = max_size;
    max_heap_ = new int[max_size];
    min_heap_ = new int[max_size];
    size_max_heap_ = 0;
    size_min_heap_ = 0;
  }

  void Destructor() {
    delete[] max_heap_;
    delete[] min_heap_;
  }

  void Insert(int value) {
    if (size_max_heap_ + size_min_heap_ == max_size_) {
      std::cout << "error\n";
      return;
    }
    max_heap_[size_max_heap_] = value;
    SiftUp(max_heap_, size_max_heap_, true);
    size_max_heap_++;

    min_heap_[size_min_heap_] = value;
    SiftUp(min_heap_, size_min_heap_, false);
    size_min_heap_++;
    std::cout << "ok\n";
  }

  void ExtractMax() {
    if (size_max_heap_ == 0) {
      std::cout << "error\n";
      return;
    }
    int max_value = max_heap_[0];
    max_heap_[0] = max_heap_[size_max_heap_ - 1];
    size_max_heap_--;
    SiftDown(max_heap_, size_max_heap_, 0, true);
    for (int i = 0; i < size_min_heap_; ++i) {
      if (min_heap_[i] == max_value) {
        min_heap_[i] = min_heap_[size_min_heap_ - 1];
        size_min_heap_--;
        SiftDown(min_heap_, size_min_heap_, i, false);
        break;
      }
    }
    std::cout << max_value << "\n";
  }

  void ExtractMin() {
    if (size_min_heap_ == 0) {
      std::cout << "error\n";
      return;
    }
    int min_value = min_heap_[0];
    min_heap_[0] = min_heap_[size_min_heap_ - 1];
    size_min_heap_--;
    SiftDown(min_heap_, size_min_heap_, 0, false);
    for (int i = 0; i < size_max_heap_; ++i) {
      if (max_heap_[i] == min_value) {
        max_heap_[i] = max_heap_[size_max_heap_ - 1];
        size_max_heap_--;
        SiftDown(max_heap_, size_max_heap_, i, true);
        break;
      }
    }
    std::cout << min_value << "\n";
  }

  void GetMax() {
    if (size_max_heap_ == 0) {
      std::cout << "error\n";
      return;
    }
    std::cout << max_heap_[0] << "\n";
  }

  void GetMin() {
    if (size_min_heap_ == 0) {
      std::cout << "error\n";
      return;
    }
    std::cout << min_heap_[0] << "\n";
  }

  void Size() {
    std::cout << size_max_heap_ << "\n";
  }

  void Clear() {
    size_max_heap_ = 0;
    size_min_heap_ = 0;
    std::cout << "ok\n";
  }
};

bool CompareStrings(const char* str1, const char* str2) {
  while (*str1 && *str2) {
    if (*str1 != *str2) {
      return false;
    }
    ++str1;
    ++str2;
  }
  return (*str1 == '\0' && *str2 == '\0');
}

int main() {
  MinMax my_struct;
  my_struct.Init(100);
  int m_count = 0;
  std::cin >> m_count;
  for (int i = 0; i < m_count; ++i) {
    char command[50];
    std::cin >> command;
    if (CompareStrings(command, "insert")) {
      int number = 0;
      std::cin >> number;
      my_struct.Insert(number);
    } else if (CompareStrings(command, "extract_min")) {
      my_struct.ExtractMin();
    } else if (CompareStrings(command, "get_min")) {
      my_struct.GetMin();
    } else if (CompareStrings(command, "extract_max")) {
      my_struct.ExtractMax();
    } else if (CompareStrings(command, "get_max")) {
      my_struct.GetMax();
    } else if (CompareStrings(command, "size")) {
      my_struct.Size();
    } else if (CompareStrings(command, "clear")) {
      my_struct.Clear();
    }
  }
  my_struct.Destructor();
  return 0;
}