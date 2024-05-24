#include "global.h"
#include "gpio.h"

int tolower(int c);
int strcasecmp(const char *str1, const char *str2);
int strncasecmp(const char *str1, const char *str2, int n);
int len(const char *str);
void strcat(char *dest, const char *src);
char *int_to_string(int num);
void strcpy(char *dest, const char *src);
void reallocate(void *dest, const void *src, int n);
void int_to_string_2(int num, char *str);
