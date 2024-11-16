#include <iostream>

void ProcessNumber(int current, bool is_primary) {
  if (current > 0) {
    ProcessNumber(current - 1, false);
    std::cout << current << ' ';
    if (is_primary) {
      ProcessNumber(current - 2, true);
    } else {
      ProcessNumber(1 - current, false);
    }
  } else if (current < 0 && !is_primary) {
    ProcessNumber(-1 - current, false);
    std::cout << current << ' ';
    ProcessNumber(1 + current, false);
  }
}

int main() {
  int input_number = 0;
  std::cin >> input_number;
  ProcessNumber(input_number, true);
  return 0;
}