#include "../header/utils.h"

// Function to convert a string to an integer
int tolower(int c) {
  if (c >= 'A' && c <= 'Z') {
    return c + ('a' - 'A');
  }
  return c;
}

// Function to compare two strings ignoring the case
int strcasecmp(const char *str1, const char *str2) {
  while (*str1 && *str2 && tolower(*str1) == tolower(*str2)) {
    str1++;
    str2++;
  }
  return tolower(*str1) - tolower(*str2);
}

// Function to compare two strings ignoring the case for n characters
int strncasecmp(const char *str1, const char *str2, int n) {
  while (n > 0 && *str1 && *str2 && tolower(*str1) == tolower(*str2)) {
    str1++;
    str2++;
    n--;
  }
  if (n == 0) {
    return 0;
  }
  return tolower(*str1) - tolower(*str2);
}

// Get length of a string
int len(const char *str) {
  int len = 0;
  while (str[len]) {
    len++;
  }
  return len;
}

// Concatenate two strings
void strcat(char *dest, const char *src) {
  while (*dest) {
    dest++;
  }
  while (*src) {
    *dest = *src;
    dest++;
    src++;
  }
  *dest = '\0';
}

void strcpy(char *dest, const char *src) {
  while (*src) {
    *dest = *src;
    dest++;
    src++;
  }
  *dest = '\0';
}

char *int_to_string(int num) {
  static char str[11];
  str[0] = '\0'; // Empty string
  int i = 0;
  if (num == 0) {
    str[i++] = '0';
  } else {
    if (num < 0) {
      str[i++] = '-';
      num = -num;
    }
    int j = 1000000000;
    while (num / j == 0) {
      j /= 10;
    }
    while (j > 0) {
      str[i++] = num / j + '0';
      num %= j;
      j /= 10;
    }
  }
  str[i] = '\0';
  return str;
}

// Function to convert integer to string
void int_to_string_2(int num, char *str) {
  int is_negative = 0;
  int temp_num = num;
  int length = 0;
  char buffer[1000];

  // Handle the special case of 0
  if (num == 0) {
    str[0] = '0';
    str[1] = '\0';
    return;
  }

  // Check if the number is negative
  if (num < 0) {
    is_negative = 1;
    temp_num = -temp_num;
  }

  // Convert each digit to a character
  while (temp_num != 0) {
    buffer[length++] = (temp_num % 10) + '0';
    temp_num /= 10;
  }

  // Add the negative sign if necessary
  if (is_negative) {
    buffer[length++] = '-';
  }

  // Reverse the string
  for (int i = 0; i < length; i++) {
    str[i] = buffer[length - 1 - i];
  }
  str[length] = '\0'; // Null-terminate the string
}
// memcpy
void reallocate(void *dest, const void *src, int n) {
  char *csrc = (char *)src;
  char *cdest = (char *)dest;
  for (int i = 0; i < n; i++) {
    cdest[i] = csrc[i];
  }
}
