#include "cstring.h"

__SIZE_TYPE__ Strlen(const char* str) {
  __SIZE_TYPE__ len = 0;
  while (str[len] != '\0') {
    len++;
  }
  return len;
}

int Strcmp(const char* first, const char* second) {
  while (*first != '\0' && *second != '\0') {
    if (*first != *second) {
      return static_cast<unsigned char>(*first) - static_cast<unsigned char>(*second);
    }
    first++;
    second++;
  }
  return static_cast<unsigned char>(*first) - static_cast<unsigned char>(*second);
}

int Strncmp(const char* first, const char* second, __SIZE_TYPE__ count) {
  __SIZE_TYPE__ index = 0;
  while (index < count && *first != '\0' && *second != '\0') {
    if (*first != *second) {
      return static_cast<unsigned char>(*first) - static_cast<unsigned char>(*second);
    }
    index++;
    first++;
    second++;
  }
  return (index < count) ? static_cast<unsigned char>(*first) - static_cast<unsigned char>(*second) : 0;
}

char* Strcpy(char* dest, const char* src) {
  char* dest_start = dest;
  while (*src != '\0') {
    *dest = *src;
    dest++;
    src++;
  }
  *dest = '\0';
  return dest_start;
}

char* Strncpy(char* dest, const char* src, __SIZE_TYPE__ count) {
  char* dest_start = dest;
  __SIZE_TYPE__ index = 0;
  while (index != count && *src != '\0') {
    *dest = *src;
    dest++;
    src++;
    index++;
  }
  while (index != count) {
    *dest = '\0';
    dest++;
    index++;
  }
  return dest_start;
}

char* Strcat(char* dest, const char* src) {
  char* dest_begin = dest;
  while (*dest != '\0') {
    dest++;
  }
  while (*src != '\0') {
    *dest = *src;
    dest++;
    src++;
  }
  *dest = '\0';
  return dest_begin;
}

char* Strncat(char* dest, const char* src, __SIZE_TYPE__ count) {
  char* dest_begin = dest;
  while (*dest != '\0') {
    dest++;
  }
  __SIZE_TYPE__ index = 0;
  while (*src != '\0' && index != count) {
    *dest = *src;
    dest++;
    src++;
    index++;
  }
  *dest = '\0';
  return dest_begin;
}

const char* Strchr(const char* str, char symbol) {
  while (*str != '\0') {
    if (*str == symbol) {
      return str;
    }
    str++;
  }
  return (symbol == '\0') ? str : nullptr;
}

const char* Strrchr(const char* str, char symbol) {
  const char* res = nullptr;
  while (*str != '\0') {
    if (*str == symbol) {
      res = str;
    }
    str++;
  }
  return (symbol == '\0') ? str : res;
}

__SIZE_TYPE__ Strspn(const char* dest, const char* src) {
  __SIZE_TYPE__ count = 0;
  while (*dest != '\0') {
    const char* temp = src;
    bool flag = false;
    while (*temp != '\0' ) {
      if (*dest == *temp) {
        flag = true;
        break;
      }
      temp++;
    }
    if (!flag) {
      return count;
    }
    count++;
    dest++;
  }
  return count;
}

__SIZE_TYPE__ Strcspn(const char* dest, const char* src) {
  __SIZE_TYPE__ count = 0;
  while (*dest != '\0') {
    const char* temp = src;
    while (*temp != '\0' ) {
      if (*dest == *temp) {
        return count;
      }
      temp++;
    }
    count++;
    dest++;
  }
  return count;
}

const char* Strpbrk(const char* dest, const char* breakset) {
  while (*dest != '\0') {
    const char* temp = breakset;
    while (*temp != '\0') {
      if (*dest == *temp) {
        return dest;
      }
      temp++;
    }
    dest++;
  }
  return nullptr;
}

const char* Strstr(const char* str, const char* pattern) {
  __SIZE_TYPE__ len_str = Strlen(str);
  __SIZE_TYPE__ len_pattern = Strlen(pattern);
  for (__SIZE_TYPE__ i = 0; i <= len_str - len_pattern; ++i) {
    if (Strncmp(str + i, pattern, len_pattern) == 0) {
      return str + i;
    }
  }
  return nullptr;
}