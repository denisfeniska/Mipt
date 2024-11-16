#include <iostream>

template <class T, class U, class R>
void Merge(const T* first_begin, const T* first_end, const U* second_begin, const U* second_end, R* out) {
  while (first_begin < first_end && second_begin < second_end) {
    if (*first_begin < *second_begin || (!(*second_begin < *first_begin) && first_begin < first_end)) {
      *out = *first_begin;
      ++first_begin;
      ++out;
    } else {
      *out = *second_begin;
      ++second_begin;
      ++out;
    }
  }
  while (first_begin < first_end) {
    *out = *first_begin;
    ++first_begin;
    ++out;
  }
  while (second_begin < second_end) {
    *out = *second_begin;
    ++second_begin;
    ++out;
  }
}

template <class T>
void Sort(T* begin, T* end) {
  if (end - begin <= 1) {
    return;
  }
  T* mid = begin + (end - begin) / 2;
  Sort(begin, mid);
  Sort(mid, end);
  T* temp = new T[end - begin];
  Merge(begin, mid, mid, end, temp);
  for (int i = 0; i < end - begin; ++i) {
    begin[i] = temp[i];
  }
  delete[] temp;
}

struct Pupil {
  char surname[41];
  char name[41];
  int inf_points;
  int math_points;
  int rus_points;
  double res_points;
  bool operator<(const Pupil& other) const {
    return res_points > other.res_points;
  }
};

int main() {
  int count_abitu = 0;
  std::cin >> count_abitu;
  auto pupils = new Pupil[count_abitu];
  for (int i = 0; i < count_abitu; ++i) {
    std::cin >> pupils[i].surname;
    std::cin >> pupils[i].name;
    std::cin >> pupils[i].inf_points;
    std::cin >> pupils[i].math_points;
    std::cin >> pupils[i].rus_points;
    pupils[i].res_points = (pupils[i].inf_points + pupils[i].math_points + pupils[i].rus_points) / 3.0;
  }
  Sort(pupils, pupils + count_abitu);
  for (int i = 0; i < count_abitu; ++i) {
    std::cout << pupils[i].surname << " " << pupils[i].name << "\n";
  }
  delete[] pupils;
  return 0;
}