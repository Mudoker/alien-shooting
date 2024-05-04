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