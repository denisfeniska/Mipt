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
  int* array_ids_;
  int* indices_;
  int max_size_;
  int size_;

  int SiftUp(int index) {
    while (index > 0) {
      int parent_index = (index - 1) / 2;
      if (values_[index] < values_[parent_index]) {
        Swap(values_[index], values_[parent_index]);
        Swap(array_ids_[index], array_ids_[parent_index]);
        Swap(indices_[index], indices_[parent_index]);
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
      int min_value_index = index;
      if (left_index < size_ && values_[min_value_index] > values_[left_index]) {
        min_value_index = left_index;
      }
      if (right_index < size_ && values_[min_value_index] > values_[right_index]) {
        min_value_index = right_index;
      }
      if (min_value_index == index) {
        return index + 1;
      }
      Swap(values_[index], values_[min_value_index]);
      Swap(array_ids_[index], array_ids_[min_value_index]);
      Swap(indices_[index], indices_[min_value_index]);
      index = min_value_index;
    }
  }

 public:
  void Init(int max_size) {
    max_size_ = max_size;
    values_ = new int[max_size];
    array_ids_ = new int[max_size];
    indices_ = new int[max_size];
    size_ = 0;
  }

  void Destructor() {
    delete[] values_;
    delete[] array_ids_;
    delete[] indices_;
  }

  void PopMin(int& array_index, int& element_index, int& min_value) {
    if (size_ == 0) {
      array_index = -1;
      element_index = -1;
      min_value = -1;
      return;
    }
    min_value = values_[0];
    array_index = array_ids_[0];
    element_index = indices_[0];
    values_[0] = values_[size_ - 1];
    array_ids_[0] = array_ids_[size_ - 1];
    indices_[0] = indices_[size_ - 1];
    size_--;
    if (size_ == 0) {
      return;
    }
    SiftDown(0);
  }

  int AddElement(int value, int array_index, int element_index) {
    if (size_ == max_size_) {
      return -1;
    }
    values_[size_] = value;
    array_ids_[size_] = array_index;
    indices_[size_] = element_index;
    size_++;
    return SiftUp(size_ - 1) + 1;
  }
};

int main() {
  int k = 0;
  std::cin >> k;
  int total_size = 0;
  int** arrays = new int*[k];
  int* sizes = new int[k];
  for (int i = 0; i < k; ++i) {
    std::cin >> sizes[i];
    arrays[i] = new int[sizes[i]];
    total_size += sizes[i];
    for (int j = 0; j < sizes[i]; ++j) {
      std::cin >> arrays[i][j];
    }
  }
  int* result = new int[total_size];
  PriorityQueue pq;
  pq.Init(k);
  for (int i = 0; i < k; ++i) {
    if (sizes[i] > 0) {
      pq.AddElement(arrays[i][0], i, 0);
    }
  }
  int result_index = 0;
  while (true) {
    int array_id = 0;
    int element_index = 0;
    int min_value = 1000001;
    pq.PopMin(array_id, element_index, min_value);
    if (array_id == -1) {
      break;
    }
    result[result_index++] = min_value;
    if (element_index + 1 < sizes[array_id]) {
      pq.AddElement(arrays[array_id][element_index + 1], array_id, element_index + 1);
    }
  }
  for (int i = 0; i < total_size; ++i) {
    std::cout << result[i] << " ";
  }
  std::cout << "\n";
  delete[] result;
  delete[] sizes;
  for (int i = 0; i < k; ++i) {
    delete[] arrays[i];
  }
  delete[] arrays;
  pq.Destructor();
  return 0;
}
