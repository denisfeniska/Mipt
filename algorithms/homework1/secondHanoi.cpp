#include <iostream>

int ThirdKernel(int kernel_from, int kernel_to) {
  if (kernel_from != 1 && kernel_to != 1) {
    return 1;
  }
  if (kernel_from != 2 && kernel_to != 2) {
    return 2;
  }
  return 3;
}

void Hanoi(int disk_number, int kernel_from, int kernel_to) {
  if (disk_number == 1) {
    std::cout << disk_number << " " << kernel_from << " " << kernel_to << "\n";
    return;
  }
  int kernel_third = ThirdKernel(kernel_from, kernel_to);
  Hanoi(disk_number - 1, kernel_from, kernel_to);
  std::cout << disk_number << " " << kernel_from << " " << kernel_third << "\n";
  Hanoi(disk_number - 1, kernel_to, kernel_from);
  std::cout << disk_number << " " << kernel_third << " " << kernel_to << "\n";
  Hanoi(disk_number - 1, kernel_from, kernel_to);
}

int main() {
  int n = 0;
  std::cin >> n;
  Hanoi(n, 1, 3);
  return 0;
}