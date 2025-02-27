#include <iostream>
#include <algorithm>

int main() {
  int pupils_count = 0;
  std::cin >> pupils_count;
  int* arr_fac = new int[pupils_count];
  for (int i = 0; i < pupils_count; ++i) {
    int fac = 0;
    std::cin >> fac;
    arr_fac[i] = fac;
  }
  std::sort(arr_fac, arr_fac + pupils_count);
  int requests_count = 0;
  std::cin >> requests_count;
  for (int i = 0; i < requests_count; ++i) {
    int request = 0;
    std::cin >> request;
    int* lower = std::lower_bound(arr_fac, arr_fac + pupils_count, request);
    int* upper = std::upper_bound(arr_fac, arr_fac + pupils_count, request);
    std::cout << (upper - lower) << "\n";
  }
  delete[] arr_fac;
  return 0;
}