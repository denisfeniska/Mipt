#include <iostream>

template <typename T>
struct Node {
  T value;
  Node* next = nullptr;
  Node* prev = nullptr;
};

template <typename T>
struct Deque {
  Node<T>* front = nullptr;
  Node<T>* back = nullptr;
  size_t size = 0;
};

template <typename T>
void push_back(Deque<T>& deque, const T& value) {
  ++deque.size;
  Node<T>* node_ptr = new Node<T>;
  node_ptr->value = value;
  if (deque.size == 1) {
    deque.back = node_ptr;
    deque.front = node_ptr;
  } else {
    node_ptr->prev = deque.back;
    deque.back->next = node_ptr;
    deque.back = node_ptr;
  }
  std::cout << "ok" << '\n';
}

template <typename T>
void push_front(Deque<T>& deque, const T& value) {
  ++deque.size;
  Node<T>* node_ptr = new Node<T>;
  node_ptr->value = value;
  if (deque.size == 1) {
    deque.front = node_ptr;
    deque.back = node_ptr;
  } else {
    node_ptr->next = deque.front;
    deque.front->prev = node_ptr;
    deque.front = node_ptr;
  }
  std::cout << "ok" << '\n';
}

template <typename T>
void pop_front(Deque<T>& deque) {
  if (deque.size == 0) {
    std::cout << "error" << '\n';
    return;
  }
  Node<T>* node_ptr = deque.front;
  T value = node_ptr->value;

  if (deque.size == 1) {
    deque.front = nullptr;
    deque.back = nullptr;
  } else {
    deque.front = deque.front->next;
    deque.front->prev = nullptr;
  }

  std::cout << value << '\n';
  --deque.size;
  delete node_ptr;
}

template <typename T>
void pop_back(Deque<T>& deque) {
  if (deque.size == 0) {
    std::cout << "error" << '\n';
    return;
  }
  Node<T>* node_ptr = deque.back;
  T value = node_ptr->value;

  if (deque.size == 1) {
    deque.front = nullptr;
    deque.back = nullptr;
  } else {
    deque.back = deque.back->prev;
    deque.back->next = nullptr;
  }

  std::cout << value << '\n';
  --deque.size;
  delete node_ptr;
}

template <typename T>
void front(Deque<T>& deque) {
  if (deque.size != 0) {
    std::cout << deque.front->value << '\n';
  } else {
    std::cout << "error" << '\n';
  }
}

template <typename T>
void back(Deque<T>& deque) {
  if (deque.size != 0) {
    std::cout << deque.back->value << '\n';
  } else {
    std::cout << "error" << '\n';
  }
}

template <typename T>
size_t size(Deque<T>& deque) {
  return deque.size;
}

template <typename T>
void clear(Deque<T>& deque) {
  while (deque.size > 0) {
    Node<T>* node_ptr = deque.front;
    deque.front = deque.front->next;
    delete node_ptr;
    --deque.size;
  }
  deque.back = nullptr;
  std::cout << "ok" << '\n';
}

void exit_program() {
  std::cout << "bye" << '\n';
}

size_t Strlen(const char* str) {
  size_t i = 0;
  while (str[i] != '\0') {
    ++i;
  }
  return i;
}

int Strcmp(const char* first, const char* second) {
  size_t len_first = Strlen(first);
  size_t len_second = Strlen(second);
  size_t len_min = std::min(len_first, len_second);
  size_t i = 0;
  int result = -3;
  while (i < len_min) {
    if (first[i] < second[i]) {
      result = -1;
      break;
    }
    if (first[i] > second[i]) {
      result = 1;
      break;
    }
    ++i;
  }
  
  if (result == -3) {
    if (len_first < len_second) {
      result = -1;
    } else if (len_first > len_second) {
      result = 1;
    } else {
      result = 0;
    }
  }
  return result;
}

int main() {
  int k = 0;
  std::cin >> k;
  Deque<int> deque;
  for (int i = 0; i < k; ++i) {
    char command[20];
    std::cin >> command;
    if (Strcmp(command, "push_front") == 0) {
      int value = 0;
      std::cin >> value;
      push_front(deque, value);
    }
    if (Strcmp(command, "push_back") == 0) {
      int value = 0;
      std::cin >> value;
      push_back(deque, value);
    }
    if (Strcmp(command, "pop_front") == 0) {
      pop_front(deque);
    }
    if (Strcmp(command, "pop_back") == 0) {
      pop_back(deque);
    }
    if (Strcmp(command, "front") == 0) {
      front(deque);
    }
    if (Strcmp(command, "back") == 0) {
      back(deque);
    }
    if (Strcmp(command, "size") == 0) {
      std::cout << size(deque) << '\n';
    }
    if (Strcmp(command, "clear") == 0) {
      clear(deque);
    }
    if (Strcmp(command, "exit") == 0) {
      exit_program();
      break;
    }
  }
  return 0;
}
