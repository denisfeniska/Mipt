#include <iostream>

struct Car {
  int time_begin;
  int time_end;
};

int main() {
  int plot_count = 0;
  std::cin >> plot_count;
  int* allowed_speed_arr = new int[plot_count];
  int* plot_len_arr = new int[plot_count];
  for (int i = 0; i < plot_count; ++i) {
    int allowed_speed = 0;
    std::cin >> allowed_speed;
    allowed_speed_arr[i] = allowed_speed;
  }
  for (int i = 0; i < plot_count; ++i) {
    int plot_len = 0;
    std::cin >> plot_len;
    plot_len_arr[i] = plot_len;
  }
  int speed_limit_count = 0;
  std::cin >> speed_limit_count;
  int* speed_limit_arr = nullptr;
  int* fine_arr = new int[speed_limit_count];
  if (speed_limit_count > 1) {
    speed_limit_arr = new int[speed_limit_count - 1];
    for (int i = 0; i < speed_limit_count - 1; ++i) {
      int speed_limit = 0;
      std::cin >> speed_limit;
      speed_limit_arr[i] = speed_limit;
    }
  }
  for (int i = 0; i < speed_limit_count; ++i) {
    int fine = 0;
    std::cin >> fine;
    fine_arr[i] = fine;
  }
  int cars_count = 0;
  std::cin >> cars_count;
  Car* cars_arr = new Car[cars_count];
  for (int i = 0; i < cars_count; ++i) {
    int time_begin = 0;
    int time_end = 0;
    std::cin >> time_begin >> time_end;
    cars_arr[i].time_begin = time_begin;
    cars_arr[i].time_end = time_end;
  }
  int* res = new int[cars_count];
  for (int i = 0; i < cars_count; ++i) {
    int time = cars_arr[i].time_end - cars_arr[i].time_begin;
    __INT64_TYPE__ len = 0;
    for (int j = 0; j < plot_count; ++j) {
      len += plot_len_arr[j];
    }
    double average_speed = static_cast<double>(len) / time;
    double max_speeding = 0.0;
    for (int j = 0; j < plot_count; ++j) {
      double time_j = static_cast<double>(plot_len_arr[j]) / average_speed;
      double speed_j = static_cast<double>(plot_len_arr[j]) / time_j;
      if (max_speeding < speed_j - allowed_speed_arr[j]) {
        max_speeding = speed_j - allowed_speed_arr[j];
      }
    }
    if (max_speeding > 0) {
      int fine = 0;
      for (int j = 0; j < speed_limit_count; ++j) {
        if (j == speed_limit_count - 1 || max_speeding <= speed_limit_arr[j]) {
          fine = fine_arr[j];
          break;
        }
      }
      res[i] = fine;
    } else {
      res[i] = 0;
    }
  }
  for (int i = 0; i < cars_count; ++i) {
    std::cout << res[i] << "\n";
  }
  delete[] allowed_speed_arr;
  delete[] plot_len_arr;
  if (speed_limit_arr != nullptr) {
    delete[] speed_limit_arr;
  }
  delete[] fine_arr;
  delete[] cars_arr;
  delete[] res;
  return 0;
}