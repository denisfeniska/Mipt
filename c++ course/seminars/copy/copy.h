#ifndef COPY_H
#define COPY_H
template <class T, class U>
U* Copy(T* arr_begin, T* arr_end, U* dest){
  int i = 0
  for (i, i < arr_end - arr_start; i++) {
    *(dest + i) = *(arr_begin + i);
  }
  return dest + i;
}
#endif