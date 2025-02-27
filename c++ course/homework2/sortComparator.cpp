#include <iostream>
#include <algorithm>

struct Struct {
  int problem_count;
  int time;
  int number;
};

int main() {
  int count = 0;
  std::cin >> count;
  auto arr = new Struct[count];
  for (int i = 0; i < count; ++i) {
    int problem_count = 0;
    int time = 0;
    std::cin >> problem_count >> time;
    arr[i].problem_count = problem_count;
    arr[i].time = time;
    arr[i].number = i;
  }
  std::sort(arr, arr + count, [](Struct first, Struct second) {
    if (first.problem_count != second.problem_count) {
      return first.problem_count > second.problem_count;
    }
    if (first.time != second.time) {
      return first.time < second.time;
    }
    return first.number < second.number;
  });
  for (int i = 0; i < count; ++i) {
    std::cout << arr[i].number + 1 << "\n";
  }
  delete[] arr;
  return 0;
}