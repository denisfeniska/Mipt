#ifndef CSTRING_H
#define CSTRING_H

__SIZE_TYPE__ Strlen(const char* str);
int Strcmp(const char* first, const char* second);
int Strncmp(const char* first, const char* second, __SIZE_TYPE__ count);
char* Strcpy(char* dest, const char* src);
char* Strncpy(char* dest, const char* src, __SIZE_TYPE__ count);
char* Strcat(char* dest, const char* src);
char* Strncat(char* dest, const char* src, __SIZE_TYPE__ count);
const char* Strchr(const char* str, char symbol);
const char* Strrchr(const char* str, char symbol);
__SIZE_TYPE__ Strspn(const char* dest, const char* src);
__SIZE_TYPE__ Strcspn(const char* dest, const char* src);
const char* Strpbrk(const char* dest, const char* breakset);
const char* Strstr(const char* str, const char* pattern);

#endif