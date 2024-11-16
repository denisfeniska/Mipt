#include <iostream>

void Hanoi(int disk_number, int kernel_from, int kernel_to, int kernel_temp) {
  if (disk_number == 1) {
    std::cout << disk_number << " " << kernel_from << " " << kernel_to << "\n";
    return;
  }
  Hanoi(disk_number - 1, kernel_from, kernel_temp, kernel_to);
  std::cout << disk_number << " " << kernel_from << " " << kernel_to << "\n";
  Hanoi(disk_number - 1, kernel_temp, kernel_to, kernel_from);
}

int main() {
  int n = 0;
  std::cin >> n;
  Hanoi(n, 1, 3, 2);
  return 0;
}